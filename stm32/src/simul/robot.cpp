#include "simul/robot.h"
#include <cmath>

#include "initkrabi.h"
#include "odometrie.h"
#include "asservissement.h"
#include "strategieV2.h"
#include "sensors.h"
#include "hardware/tourelle.h"
#include "actionneurs/benne.h"
#include <iostream>
#include <QDebug>

#define ratio_qt_box2d 0.01

Robot::Robot(b2World & world, bool manual, bool isYellow) : world(world), olds(10000), body(NULL), mRemoteMod(false)
{
    this->manual = manual;
    level = 0;

    qDebug() << "Robot :" << isYellow;

    //Initialisation ini = new Initialisation(PositionPlusAngle(Position(300, 1000), 0), isYellow, this);
    InitKrabi initKrabi(isYellow, this);
    initKrabi.init();

    odometrie = initKrabi.getOdometrie();
    asservissement = initKrabi.getAsservissement();
    strategie = initKrabi.getStrategie();

    this->isYellow = isYellow;    //new Sensors();

    deriv.position.x = 0;
    deriv.position.y = 0;
    deriv.angle = 0;

    /// Déclaration graphique (QT)
    int inc = 0;


    //Krabi 2016
#ifdef KRABI
    // NB: les points doivent être entrés dans le sens anti-horaire
    robotPolygonPoints.push_back(QPoint(350/2,250/2));
    robotPolygonPoints.push_back(QPoint(-350/2,250/2));
    robotPolygonPoints.push_back(QPoint(-350/2,-250/2));
    robotPolygonPoints.push_back(QPoint(350/2,-250/2));
#endif

#ifdef KRABI_JR
    robotPolygonPoints.push_back(QPoint(86,0));
    robotPolygonPoints.push_back(QPoint(86,94));
    robotPolygonPoints.push_back(QPoint(64,115));
    robotPolygonPoints.push_back(QPoint(-40,115));
    robotPolygonPoints.push_back(QPoint(-40,-115));
    robotPolygonPoints.push_back(QPoint(64,-115));
    robotPolygonPoints.push_back(QPoint(86,-94));
    robotPolygonPoints.push_back(QPoint(86,-0));
#endif

    /*** Déclaration Physique (Box2D) ***/
    b2BodyDef bodyDef;
#ifndef BOX2D_2_0_1
    bodyDef.type = b2_dynamicBody;
#endif
    bodyDef.position.Set(pos.position.x/100., pos.position.y/100.);
    bodyDef.angle = pos.angle;

    body = world.CreateBody(&bodyDef); // Si le code plante ici, c'est souvent parceque les nombres d'étapes dans strategieV3.cpp et dans strategie.h ne correspondent pas


#ifdef BOX2D_2_0_1
    b2PolygonDef box;
    b2PolygonDef &fixture = box;
#define CreateFixture CreateShape
#else
    b2PolygonShape box;
    b2FixtureDef fixture;
    fixture.shape = &box;
#endif
    fixture.density = 10.0f;
    fixture.friction = 1.0f;


#ifdef BOX2D_2_0_1
    b2Vec2* v = box.vertices;
    box.vertexCount = robotPolygonPoints.size();
#else
    std::vector<b2Vec2> v;
    v.reserve(16);
#endif
    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    // 2dbox limite à 8 le nombre de vertex par polygone
    inc = 0;

    for(size_t i = 0; i < robotPolygonPoints.size(); i += 1)
    {
        v[0].Set(0., 0.);
        v[1].Set(robotPolygonPoints[i].x() * ratio_qt_box2d, robotPolygonPoints[i].y() * ratio_qt_box2d);
        v[2].Set(robotPolygonPoints[(i + 1) % robotPolygonPoints.size()].x() * ratio_qt_box2d,
                 robotPolygonPoints[(i + 1) % robotPolygonPoints.size()].y() * ratio_qt_box2d);
        //v[3].Set(robotPolygonPoints[i + 2].x() * ratio_qt_box2d, robotPolygonPoints[i + 2].y() * ratio_qt_box2d);

#ifndef BOX2D_2_0_1
        box.Set(v.data(), 3);
#endif
        fixture.filter.categoryBits=0x9;
        body->CreateFixture(&fixture);
    }

    //Little hack so that linear and angular speed of the object
    //are those of the local coord (0,0) of the robot.
    //We don't really care of the mass center accuracy.
    b2MassData md;
    body->GetMassData(&md);
    md.center = b2Vec2(0,0);
    body->SetMassData(&md);

    // SENSORS :

    SharpSensor** sharpsList = strategie->getSensors();

    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp avant droit
    inc = 0;

    //Krabi 2014
    v[inc++].Set(161.f*ratio_qt_box2d,-97.f*ratio_qt_box2d);
    v[inc++].Set(211.f*ratio_qt_box2d,-97.f*ratio_qt_box2d);
    v[inc++].Set(211.f*ratio_qt_box2d,-42.f*ratio_qt_box2d);
    v[inc++].Set(161.f*ratio_qt_box2d,-42.f*ratio_qt_box2d);

#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif

    fixture.isSensor=true;

    capteurSharpAvantDroit.type = 1;
    capteurSharpAvantDroit.object = sharpsList[1];
    fixture.userData=(void*)&capteurSharpAvantDroit;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);


    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp avant gauche
    inc = 0;

    //Krabi 2014
    v[inc++].Set(161.f*ratio_qt_box2d,42.f*ratio_qt_box2d);
    v[inc++].Set(211.f*ratio_qt_box2d,42.f*ratio_qt_box2d);
    v[inc++].Set(211.f*ratio_qt_box2d,97.f*ratio_qt_box2d);
    v[inc++].Set(161.f*ratio_qt_box2d,97.f*ratio_qt_box2d);

#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif
    fixture.isSensor=true;

    capteurSharpAvantGauche.type = 1;
    capteurSharpAvantGauche.object = sharpsList[0];
    fixture.userData=(void*)&capteurSharpAvantGauche;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);

    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp cote droit
    inc = 0;

    //Krabi 2014
    v[inc++].Set(102.f*ratio_qt_box2d,-150.f*ratio_qt_box2d);
    v[inc++].Set(142.f*ratio_qt_box2d,-180.f*ratio_qt_box2d);
    v[inc++].Set(173.f*ratio_qt_box2d,-153.5f*ratio_qt_box2d);
    v[inc++].Set(133.f*ratio_qt_box2d,-123.f*ratio_qt_box2d);

#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif

    fixture.isSensor=true;

    capteurSharpcoteDroit.type = 1;
    capteurSharpcoteDroit.object = sharpsList[3];
    fixture.userData=(void*)&capteurSharpcoteDroit;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);

    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp cote gauche
    inc = 0;

    //Krabi 2014
    v[inc++].Set(133.f*ratio_qt_box2d,123.f*ratio_qt_box2d);
    v[inc++].Set(173.f*ratio_qt_box2d,153.f*ratio_qt_box2d);
    v[inc++].Set(142.f*ratio_qt_box2d,180.f*ratio_qt_box2d);
    v[inc++].Set(102.f*ratio_qt_box2d,150.f*ratio_qt_box2d);


#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif

    fixture.isSensor=true;

    capteurSharpcoteGauche.type = 1;
    capteurSharpcoteGauche.object = sharpsList[2];
    fixture.userData=(void*)&capteurSharpcoteGauche;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);

    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp arriere milieu
    inc = 0;

    //Krabi 2014
    v[inc++].Set(-128.f*ratio_qt_box2d,25.f*ratio_qt_box2d);
    v[inc++].Set(-178.f*ratio_qt_box2d,25.f*ratio_qt_box2d);
    v[inc++].Set(-178.f*ratio_qt_box2d,-25.f*ratio_qt_box2d);
    v[inc++].Set(-128.f*ratio_qt_box2d,-25.f*ratio_qt_box2d);


#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif

    fixture.isSensor=true;

    capteurSharpArriereMilieu.type = 1;
    capteurSharpArriereMilieu.object = sharpsList[5];
    fixture.userData=(void*)&capteurSharpArriereMilieu;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);

    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp arriere droit
    inc = 0;

    //Krabi 2014
#ifdef KRABI
    v[inc++].Set(-128.f*ratio_qt_box2d,-90.f*ratio_qt_box2d);
    v[inc++].Set(-178.f*ratio_qt_box2d,-90.f*ratio_qt_box2d);
    v[inc++].Set(-160.f*ratio_qt_box2d,-140.f*ratio_qt_box2d);
    v[inc++].Set(-111.f*ratio_qt_box2d,-140.f*ratio_qt_box2d);
#endif

    //Krabi Jr 2014
#ifdef KRABI_JR
    v[inc++].Set(-128.f*ratio_qt_box2d,-90.f*ratio_qt_box2d);
    v[inc++].Set(-178.f*ratio_qt_box2d,-90.f*ratio_qt_box2d);
    v[inc++].Set(-160.f*ratio_qt_box2d,-140.f*ratio_qt_box2d);
    v[inc++].Set(-111.f*ratio_qt_box2d,-140.f*ratio_qt_box2d);
#endif

#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif

    fixture.isSensor=true;

    capteurSharpArriereDroit.type = 1;
    capteurSharpArriereDroit.object = sharpsList[6];
    fixture.userData=(void*)&capteurSharpArriereDroit;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);

    // on déclare les points d'une partie : Attention, doit être convexe et orientée dans le sens indirect
    //Capteur sharp arriere gauche
    inc = 0;

    //Krabi 2014
    v[inc++].Set(-111.f*ratio_qt_box2d,140.f*ratio_qt_box2d);
    v[inc++].Set(-160.f*ratio_qt_box2d,140.f*ratio_qt_box2d);
    v[inc++].Set(-178.f*ratio_qt_box2d,90.f*ratio_qt_box2d);
    v[inc++].Set(-128.f*ratio_qt_box2d,90.f*ratio_qt_box2d);

#ifndef BOX2D_2_0_1
    box.Set(v.data(), 4);
#endif

    fixture.isSensor=true;

    capteurSharpArriereGauche.type = 1;
    capteurSharpArriereGauche.object = sharpsList[4];
    fixture.userData=(void*)&capteurSharpArriereGauche;
    fixture.filter.maskBits=0x8;
    fixture.filter.categoryBits=0x1;
    body->CreateFixture(&fixture);

}

Robot::~Robot()
{
    delete asservissement;
    delete odometrie;
    delete strategie;
    world.DestroyBody(body);
}

void Robot::updateForces(int dt)
{
    if(dt == 0)
        return;

    Position impulse;
    impulse.x = (deriv.position.x*(float)cos(pos.angle) - deriv.position.y*(float)sin(pos.angle));
    impulse.y = (deriv.position.x*(float)sin(pos.angle) + deriv.position.y*(float)cos(pos.angle));

    float32 rdt = 1000./(float)dt;

    b2Vec2 bvelocity = 0.01*rdt*b2Vec2(impulse.x,impulse.y);
    float bangular = deriv.angle*rdt;
    //body->ApplyForce(10*body->GetMass()*(bimpulse - body->GetLinearVelocity()), body->GetWorldCenter());
    //body->ApplyTorque((bangular - body->GetAngularVelocity())*body->GetInertia());

    body->SetLinearVelocity(bvelocity);
    body->SetAngularVelocity(bangular);
}


void Robot::paint(QPainter &p, int dt)
{
    if(dt)
    {
        pos.position.x = 100*body->GetPosition().x;
        pos.position.y = 100*body->GetPosition().y;
        pos.angle = body->GetAngle();

        float rdt = (float)dt/1000.;
        deriv.angle = body->GetAngularVelocity()*rdt;
        float derx = 100*body->GetLinearVelocity().x*rdt;
        float dery = 100*body->GetLinearVelocity().y*rdt;

        deriv.position.x = derx*cos(pos.angle) + dery*sin(pos.angle);
        deriv.position.y = 0;

        //olds.push_back(pos);
        if(manual || mRemoteMod)
        {
            keyPressEvent(NULL,false);
            deriv.position.x = deriv.position.x* 0.97f;
            deriv.angle = deriv.angle * 0.9;
        }
        else
        {
            Benne::getInstance()->update();
            Odometrie::odometrie->update();
            Tourelle::getSingleton()->update();
            StrategieV2::update();
            Asservissement::asservissement->update();
            deriv.position.x = asservissement->getLinearSpeed();
            deriv.position.y = 0;
            deriv.angle = asservissement->getAngularSpeed();
        }

        // hammers update

        if (leftLowerHammerStatus == 100)
            leftLowerHammerStatus = 0;
        if (rightLowerHammerStatus == 100)
            rightLowerHammerStatus = 0;
        if (leftUpperHammerStatus == 200)
            leftUpperHammerStatus = 0;
        if (rightUpperHammerStatus == 200)
            rightUpperHammerStatus = 0;

        if (leftLowerHammerStatus > 0)
            leftLowerHammerStatus += (int)(dt/2);
        if (rightLowerHammerStatus > 0)
            rightLowerHammerStatus += (int)(dt/2);
        if (leftUpperHammerStatus > 0)
            leftUpperHammerStatus += (int)(dt);
        if (rightUpperHammerStatus > 0)
            rightUpperHammerStatus += (int)(dt);

        if (leftLowerHammerStatus > 100)
            leftLowerHammerStatus = 100;
        if (rightLowerHammerStatus > 100)
            rightLowerHammerStatus = 100;
        if (leftUpperHammerStatus > 200)
            leftUpperHammerStatus = 200;
        if (rightUpperHammerStatus > 200)
            rightUpperHammerStatus = 200;

    }

    p.setWorldTransform(QTransform().translate(pos.position.x,pos.position.y).rotateRadians(pos.angle));


    p.setPen(QColor(Qt::black));
    p.setBrush(QBrush(QColor(90,90,90)));
    p.setOpacity(.3);

    // on peint le robot.
    p.drawConvexPolygon(robotPolygonPoints.data(), robotPolygonPoints.size());
    /*p.drawRect(-20, 160, 20, rightUpperHammerStatus);
    p.drawRect(0, 160, 20, rightLowerHammerStatus);
    p.drawRect(-20, -160, 20, -leftUpperHammerStatus);
    p.drawRect(0, -160, 20, -leftLowerHammerStatus);*/

    //On peint le carré de la couleur du départ
    if(!isYellow)
    {
        p.setPen(QColor(Qt::green));
        p.setBrush(QBrush(Qt::green));//QColor(90,90,90)));
    }
    else
    {
        p.setPen(QColor(Qt::yellow));
        p.setBrush(QBrush(Qt::yellow));//QColor(90,90,90)));
    }
    p.setOpacity(.3);
    p.drawRect(-40, -40, 80, 80);

    if(true)//On dessine les champs des capteurs
    {
        p.setPen(QColor(Qt::red));
        p.setBrush(QBrush(QColor(255,0,0)));
        p.setOpacity(.2);

        //Krabi 2014
        #ifdef KRABI
            QPolygon polygonCapteurSharpAvantGauche;
            polygonCapteurSharpAvantGauche << QPoint(161.f,-97.f) << QPoint(211.f,-97.f)
                    << QPoint(211.f,-42.f) << QPoint(161.f,-42.f);
            p.drawPolygon(polygonCapteurSharpAvantGauche);

            QPolygon polygonCapteurSharpAvantDroit;
            polygonCapteurSharpAvantDroit << QPoint(161.f,97.f) << QPoint(211.f,97.f)
                     << QPoint(211.f,42.f) << QPoint(161.f,42.f);
            p.drawPolygon(polygonCapteurSharpAvantDroit);

            QPolygon polygonCapteurSharpcoteGauche;
            polygonCapteurSharpcoteGauche << QPoint(102.f,-150.f) << QPoint(142.f,-180.f)
                    << QPoint(173.f,-153.f) << QPoint(133.f,-123.f);
            p.drawPolygon(polygonCapteurSharpcoteGauche);

            QPolygon polygonCapteurSharpcoteDroit;
            polygonCapteurSharpcoteDroit << QPoint(102.f,150.f) << QPoint(142.f,180.f)
                    << QPoint(173.f,153.f) << QPoint(133.f,123.f);
            p.drawPolygon(polygonCapteurSharpcoteDroit);

            QPolygon polygonCapteurSharpArriereDroit;
            polygonCapteurSharpArriereDroit << QPoint(-111.f,140.f) << QPoint(-160.f,140.f)
                    << QPoint(-178.f,90.f) << QPoint(-128.f,90.f);
            p.drawPolygon(polygonCapteurSharpArriereDroit);

            QPolygon polygonCapteurSharpArriereMilieu;
            polygonCapteurSharpArriereMilieu << QPoint(-128.f,-25) << QPoint(-178.f,-25.f)
                    << QPoint(-178.f,25.f) << QPoint(-128.f,25.f);
            p.drawPolygon(polygonCapteurSharpArriereMilieu);

            QPolygon polygonCapteurSharpArriereGauche;
            polygonCapteurSharpArriereGauche << QPoint(-111.f,-140.f) << QPoint(-160.f,-140.f)
                    << QPoint(-178.f,-90.f) << QPoint(-128.f,-90.f);
            p.drawPolygon(polygonCapteurSharpArriereGauche);
        #endif

        #ifdef KRABI_JR
            QPolygon polygonCapteurSharpAvantGauche;
            polygonCapteurSharpAvantGauche << QPoint(161.f,-97.f) << QPoint(211.f,-97.f)
                    << QPoint(211.f,-42.f) << QPoint(161.f,-42.f);
            p.drawPolygon(polygonCapteurSharpAvantGauche);

            QPolygon polygonCapteurSharpAvantDroit;
            polygonCapteurSharpAvantDroit << QPoint(161.f,97.f) << QPoint(211.f,97.f)
                     << QPoint(211.f,42.f) << QPoint(161.f,42.f);
            p.drawPolygon(polygonCapteurSharpAvantDroit);

            QPolygon polygonCapteurSharpcoteGauche;
            polygonCapteurSharpcoteGauche << QPoint(102.f,-150.f) << QPoint(142.f,-180.f)
                    << QPoint(173.f,-153.f) << QPoint(133.f,-123.f);
            p.drawPolygon(polygonCapteurSharpcoteGauche);

            QPolygon polygonCapteurSharpcoteDroit;
            polygonCapteurSharpcoteDroit << QPoint(102.f,150.f) << QPoint(142.f,180.f)
                    << QPoint(173.f,153.f) << QPoint(133.f,123.f);
            p.drawPolygon(polygonCapteurSharpcoteDroit);

            QPolygon polygonCapteurSharpArriereDroit;
            polygonCapteurSharpArriereDroit << QPoint(-111.f,140.f) << QPoint(-160.f,140.f)
                    << QPoint(-178.f,90.f) << QPoint(-128.f,90.f);
            p.drawPolygon(polygonCapteurSharpArriereDroit);

            QPolygon polygonCapteurSharpArriereMilieu;
            polygonCapteurSharpArriereMilieu << QPoint(-128.f,-25) << QPoint(-178.f,-25.f)
                    << QPoint(-178.f,25.f) << QPoint(-128.f,25.f);
            p.drawPolygon(polygonCapteurSharpArriereMilieu);

            QPolygon polygonCapteurSharpArriereGauche;
            polygonCapteurSharpArriereGauche << QPoint(-111.f,-140.f) << QPoint(-160.f,-140.f)
                    << QPoint(-178.f,-90.f) << QPoint(-128.f,-90.f);
            p.drawPolygon(polygonCapteurSharpArriereGauche);
        #endif

         p.setPen(QColor(Qt::black));
         p.setBrush(QBrush(QColor(90,90,90)));
         p.setOpacity(.3);
    }


    //On affiche les LEDs de débug
    //int nbLed = sizeof(ledIsOn)/sizeof(int);

    for(int numeroLed = 0 ; numeroLed<NB_LED ; numeroLed++)
    {
        if (isLedOn(numeroLed))
        {
            p.setOpacity(1);
            if(numeroLed==0)
            {
                p.setPen(QColor("orange"));
                p.setBrush(QBrush("orange"));
            }
            else if(numeroLed==1)
            {
                p.setPen(QColor("green"));
                p.setBrush(QBrush("green"));
            }
            else
            {
                p.setPen(QColor(255,0,0));
                p.setBrush(QBrush(QColor(255,0,0)));
            }

            p.drawEllipse(QPoint(0,(int)(numeroLed*100-50*(NB_LED-1))),10,-10);
        }
    }

    //p.drawChord(-103/2 + 104, -107, 2*103, 215, 16*90, 16*180);
    //p.drawRect(-268, -179.5, 268, 359);
    //drawTriangle(p, 0, 0,  65, 0,  60, 0);
    p.setOpacity(1);

    /*p.setPen(QColor(Qt::red));
    p.drawLine(0,0,pos.position.x,0);
    p.drawLine(0,100*pos.angle,0,0);*/
    p.setWorldTransform(QTransform());


    p.setPen(QColor(Qt::green));
    for(unsigned int i=0; i+1 < olds.size(); i++)
        p.drawLine(olds[i].position.x, -olds[i].position.y, olds[i+1].position.x, -olds[i+1].position.y);
}

#define IF_KEYSWITCH(n,a) \
static bool n=false; \
if(evt) n= a ? press : n; if(n)

void Robot::keyPressEvent(QKeyEvent* evt, bool press)
{
    if(evt && press && evt->text() == "e" && !evt->isAutoRepeat())
        manual = !manual;


    if(evt && press && evt->text() == "u" && !evt->isAutoRepeat())
    {
        level = (level != 100) ? 100 : 0;
#ifdef BOX2D_2_0_1
#define b2Filter b2FilterData
#define GetFixtureList GetShapeList
#endif
        b2Filter filter;
        if(level == 100)
        {
            filter.categoryBits = 0x4;
            filter.maskBits = 0x3;
        }
        else
        {
            filter.maskBits = 0x3;
            filter.categoryBits = 0x1;
        }
    }


    if(!mRemoteMod && manual)
    {
        float dinc = .25;
        float ainc = 0.0025;

        IF_KEYSWITCH(avant,evt->key() == Qt::Key_Up)
            deriv.position.x += dinc;
        IF_KEYSWITCH(arriere,evt->key() == Qt::Key_Down)
            deriv.position.x -= dinc;
        IF_KEYSWITCH(gauche,evt->key() == Qt::Key_Right)
            deriv.angle += ainc;
        IF_KEYSWITCH(droite,evt->key() == Qt::Key_Left)
            deriv.angle -= ainc;
        IF_KEYSWITCH(leftUpperHammerUp,evt->key() == Qt::Key_W)
            leftUpperHammerStatus = 1;
        IF_KEYSWITCH(leftUpperHammerDown,evt->key() == Qt::Key_X)
            leftLowerHammerStatus = 1;
        IF_KEYSWITCH(rightUpperHammerUp,evt->key() == Qt::Key_C)
            rightUpperHammerStatus = 1;
        IF_KEYSWITCH(rightUpperHammerDown,evt->key() == Qt::Key_V)
            rightLowerHammerStatus = 1;

    }
    else // automated robot
    {
        IF_KEYSWITCH(leftUpperHammerUp,evt->key() == Qt::Key_O)
            StrategieV2::willCollide();
    }
}

void Robot::setLevel()
{
            level = (level != 100) ? 100 : 0;
#ifdef BOX2D_2_0_1
#define b2Filter b2FilterData
#define GetFixtureList GetShapeList
#endif
        b2Filter filter;
        if(level == 100)
        {
            filter.categoryBits = 0x4;
            filter.maskBits = 0x3;
        }
        else
        {
            filter.maskBits = 0x3;
            filter.categoryBits = 0x1;
        }
}

PositionPlusAngle Robot::getPos()
{
    float alea1 = 0., alea2 = 0., alea3 = 0.;
 /*   alea1 = 2.1*(rand() % 801 -400)/1000;
    alea2 = 2.1*(rand() % 801 -400)/1000;
    alea3 = 2.1*(rand() % 801 -400)/6000; */
    Vec3d erreur(alea1, alea2, alea3);
    return (pos + erreur);
}

void Robot::setPos(PositionPlusAngle p)
{
    pos = p;
    if (body != NULL)
        body->SetTransform(b2Vec2(p.position.x * ratio_qt_box2d, p.position.y * ratio_qt_box2d), p.angle);
}

Angle Robot::getVitesseAngulaire()
{
    return deriv.angle;
}

Distance Robot::getVitesseLineaire()
{
    return deriv.position.x;
}

void Robot::setRemoteMod(bool remote)
{
    mRemoteMod = remote;
}

QPoint Robot::getLeftUpperHammerPos() const
{
    return QPoint((this->pos.position.x - (160 + leftUpperHammerStatus - 10)*sin(pos.angle)), -(this->pos.position.y + (160 + leftUpperHammerStatus-10)*cos(pos.angle)));
}
QPoint Robot::getRightUpperHammerPos() const
{
    return QPoint(this->pos.position.x + (160 + rightUpperHammerStatus -10)*sin(pos.angle), -(this->pos.position.y - (160 + rightUpperHammerStatus-10)*cos(pos.angle)));
}
QPoint Robot::getLeftLowerHammerPos() const
{
    return QPoint(this->pos.position.x - (160 + leftLowerHammerStatus-10)*sin(pos.angle) , -(this->pos.position.y + (160 + leftLowerHammerStatus-10)*cos(pos.angle)));
}
QPoint Robot::getRightLowerHammerPos() const
{
    return QPoint(this->pos.position.x + (160 + rightLowerHammerStatus-10)*sin(pos.angle), -(this->pos.position.y - (160 + rightLowerHammerStatus-10)*cos(pos.angle)));
}
void Robot::startLeftUpperHammer()
{
    leftUpperHammerStatus = 1;
}
void Robot::startRightUpperHammer()
{
    rightUpperHammerStatus = 1;
}
void Robot::startLeftLowerHammer()
{
    leftLowerHammerStatus = 1;
}
void Robot::startRightLowerHammer()
{
    leftUpperHammerStatus = 1;
}

void Robot::paintStrategie(QPainter& p)
{
    strategie->paint(&p);
}
