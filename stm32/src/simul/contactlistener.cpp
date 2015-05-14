#include "contactlistener.h"
#include "userdata.h"
#include "sharpSensor.h"
#include <iostream>
#include <QDebug>

ContactListener::ContactListener() : b2ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    void* myUserDataA = contact->GetFixtureA()->GetUserData();
    void* myUserDataB = contact->GetFixtureB()->GetUserData();

    if(myUserDataA)
    {
        struct UserData *myStructuredUserData = (UserData*) myUserDataA;

        if(myStructuredUserData->type == 1)// Si c'est un capteur
        {
            SharpSensor *detectingSharpSensor = (SharpSensor*) myStructuredUserData->object;
            detectingSharpSensor->setEvent();
#ifndef ROBOTHW
            qDebug() << "Sensor " << detectingSharpSensor->getName() << " is detecting something !!!\n";
#endif
        }
    }

    if(myUserDataB)
    {
        struct UserData *myStructuredUserData = (UserData*) myUserDataB;

        if(myStructuredUserData->type == 1)// Si c'est un capteur
        {
            SharpSensor *detectingSharpSensor = (SharpSensor*) myStructuredUserData->object;
            detectingSharpSensor->setEvent();
#ifndef ROBOTHW
            qDebug() << "Sensor " << detectingSharpSensor->getName() << " is detecting something !!!\n";
#endif
        }
    }
}



void ContactListener::EndContact(b2Contact* contact)
{
    void* myUserDataA = contact->GetFixtureA()->GetUserData();
    void* myUserDataB = contact->GetFixtureB()->GetUserData();

    if(myUserDataA)
    {
        struct UserData *myStructuredUserData = (UserData*) myUserDataA;

        if(myStructuredUserData->type == 1)// Si c'est un capteur
        {
            SharpSensor *detectingSharpSensor = (SharpSensor*) myStructuredUserData->object;
            detectingSharpSensor->unsetEvent();
#ifndef ROBOTHW
            qDebug() << "Sensor " << detectingSharpSensor->getName() << " has stopped detecting something !!!\n";
#endif
        }
    }

    if(myUserDataB)
    {
        struct UserData *myStructuredUserData = (UserData*) myUserDataB;

        if(myStructuredUserData->type == 1)// Si c'est un capteur
        {
            SharpSensor *detectingSharpSensor = (SharpSensor*) myStructuredUserData->object;
            detectingSharpSensor->unsetEvent();
#ifndef ROBOTHW
            qDebug() << "Sensor " << detectingSharpSensor->getName() << " has stopped detecting something !!!\n";
#endif
        }
    }
}



void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}



void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
   /* void* bodyUserDataA = contact->GetFixtureA()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetUserData();
    if(bodyUserDataA)
    {
        contact->GetFixtureA()->GetBody()->DestroyFixture(contact->GetFixtureA());
    }
    if(bodyUserDataB)
    {
        contact->GetFixtureB()->GetBody()->DestroyFixture(contact->GetFixtureB());
    }*/
}
