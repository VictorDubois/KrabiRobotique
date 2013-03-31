#include <Arduino.h>
#include "Scarabi.h"
#include "Move.h"
//#include "Diode.h"
#include <Servo.h>

// PROTOPTYPES DES FONCTIONS //
void setup() //premiere fonction appelée.
{
    // Debug
    pinMode(13, OUTPUT);
    // Initialize serial communication:
    Serial.begin(115200);
    Serial.println("Starting Up...");

    Scarabi::singleton()->waitTirette(false);

    //Move::singleton()->addAction(DELAY,50);
    //Move::singleton()->addAction(MOVE_45CLOCK,0.5);
    if (Scarabi::singleton()->getColor()==Scarabi::colorRed)
        Move::singleton()->setInversedSense(true);
    if (true)
    {
        //Sortie de la zone de départ
        Move::singleton()->addAction(MOVE_FORWARD,45);
        //Move::singleton()->addAction(MOVE_BACKWARD,40);
        //Premier cadeau
        Move::singleton()->addAction(MOVE_45CLOCK,2);
        Move::singleton()->addAction(DISABLE_SHARPS);
        Move::singleton()->addAction(MOVE_FORWARD,40);
        Move::singleton()->addAction(ENABLE_SHARPS);
        Move::singleton()->addAction(MOVE_BACKWARD,15);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,55);
        //Deuxième cadeau
        Move::singleton()->addAction(MOVE_45CLOCK,2);
        Move::singleton()->addAction(DISABLE_SHARPS);
        Move::singleton()->addAction(MOVE_FORWARD,40);
        Move::singleton()->addAction(ENABLE_SHARPS);
        Move::singleton()->addAction(MOVE_BACKWARD,15);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,56);
        //Troisième cadeau
        Move::singleton()->addAction(MOVE_45CLOCK,2);
        Move::singleton()->addAction(DISABLE_SHARPS);
        Move::singleton()->addAction(MOVE_FORWARD,40);
        Move::singleton()->addAction(ENABLE_SHARPS);
        Move::singleton()->addAction(MOVE_BACKWARD,15);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,2.2);
        Move::singleton()->addAction(MOVE_FORWARD,64);
        //Quatrième cadeau
        Move::singleton()->addAction(MOVE_45CLOCK,2.4);
        Move::singleton()->addAction(DISABLE_SHARPS);
        Move::singleton()->addAction(MOVE_FORWARD,40);
        Move::singleton()->addAction(ENABLE_SHARPS);
        Move::singleton()->addAction(MOVE_BACKWARD,40);
        /*Move::singleton()->addAction(MOVE_45ANTICLOCK,4);
        Move::singleton()->addAction(MOVE_FORWARD,5);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1.1);
        Move::singleton()->addAction(MOVE_FORWARD,45);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,2.5);
        Move::singleton()->addAction(MOVE_FORWARD,45);
        Move::singleton()->addAction(MOVE_45CLOCK,1.5);
        Move::singleton()->addAction(MOVE_FORWARD,210);
        Move::singleton()->addAction(MOVE_BACKWARD,25);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,4.2);
        Move::singleton()->addAction(MOVE_FORWARD,90);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1);
        Move::singleton()->addAction(MOVE_FORWARD,7);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1);
        Move::singleton()->addAction(MOVE_FORWARD,7);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1);
        Move::singleton()->addAction(MOVE_FORWARD,7);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1.5);
        Move::singleton()->addAction(MOVE_FORWARD,120);*/
        //Verres retour zone de départ
        Move::singleton()->addAction(MOVE_45CLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,75);
        Move::singleton()->addAction(MOVE_45CLOCK,0.35);
        Move::singleton()->addAction(MOVE_FORWARD,75);
        Move::singleton()->addAction(MOVE_45CLOCK,0.35);
        Move::singleton()->addAction(MOVE_FORWARD,50);
        //Aller ligne 2 de verres
        Move::singleton()->addAction(MOVE_BACKWARD,200);
        //Retour ligne 2 de verres
        Move::singleton()->addAction(MOVE_45CLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,25);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,50);
        Move::singleton()->addAction(MOVE_45CLOCK,0.25);
        Move::singleton()->addAction(MOVE_FORWARD,150);
        //Aller ligne 3 de verres
        Move::singleton()->addAction(MOVE_BACKWARD,200);
        //Retour ligne 3 de verres
        Move::singleton()->addAction(MOVE_45CLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,35);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,2);
        Move::singleton()->addAction(MOVE_FORWARD,200);
        /*Move::singleton()->addAction(MOVE_FORWARD,50);
        Move::singleton()->addAction(MOVE_45CLOCK,0.25);
        Move::singleton()->addAction(MOVE_FORWARD,50);*/

        /*Move::singleton()->addAction(MOVE_BACKWARD,25);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,4);
        Move::singleton()->addAction(MOVE_FORWARD,90);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1);
        Move::singleton()->addAction(MOVE_FORWARD,40);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,3);
        Move::singleton()->addAction(MOVE_FORWARD,125);

        /*Move::singleton()->addAction(MOVE_BACKWARD,25);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,4.2);
        Move::singleton()->addAction(MOVE_FORWARD,120);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,1);
        Move::singleton()->addAction(MOVE_FORWARD,25);
        Move::singleton()->addAction(MOVE_45ANTICLOCK,3.5);
        Move::singleton()->addAction(MOVE_FORWARD,150);*/
    }
    /*else
    {
        Move::singleton()->addAction(MOVE_FORWARD,2);
        Move::singleton()->addAction(DISABLE_SHARPS);
        Move::singleton()->addAction(MOVE_FORWARD,2);
        Move::singleton()->addAction(ENABLE_SHARPS);
        Move::singleton()->addAction(MOVE_FORWARD,60);
    }*/
}

void loop()
{
    Scarabi::singleton()->update();
    if (false)
    {
        //Sortie de la zone de départ
        Move::singleton()->perform(MOVE_FORWARD,45);
        //Move::singleton()->perform(MOVE_BACKWARD,40);
        //Premier cadeau
        Move::singleton()->perform(MOVE_45CLOCK,2);
        Move::singleton()->perform(DISABLE_SHARPS);
        Move::singleton()->perform(MOVE_FORWARD,45);
        Move::singleton()->perform(ENABLE_SHARPS);
        Move::singleton()->perform(MOVE_BACKWARD,15);
        Move::singleton()->perform(MOVE_45ANTICLOCK,2);
        Move::singleton()->perform(MOVE_FORWARD,55);
        //Deuxième cadeau
        Move::singleton()->perform(MOVE_45CLOCK,2);
        Move::singleton()->perform(DISABLE_SHARPS);
        Move::singleton()->perform(MOVE_FORWARD,45);
        Move::singleton()->perform(ENABLE_SHARPS);
        Move::singleton()->perform(MOVE_BACKWARD,15);
        Move::singleton()->perform(MOVE_45ANTICLOCK,2);
        Move::singleton()->perform(MOVE_FORWARD,56);
        //Troisième cadeau
        Move::singleton()->perform(MOVE_45CLOCK,2);
        Move::singleton()->perform(DISABLE_SHARPS);
        Move::singleton()->perform(MOVE_FORWARD,45);
        Move::singleton()->perform(ENABLE_SHARPS);
        Move::singleton()->perform(MOVE_BACKWARD,15);
        Move::singleton()->perform(MOVE_45ANTICLOCK,2.2);
        Move::singleton()->perform(MOVE_FORWARD,60);
        //Quatrième cadeau
        Move::singleton()->perform(MOVE_45CLOCK,2.4);
        Move::singleton()->perform(DISABLE_SHARPS);
        Move::singleton()->perform(MOVE_FORWARD,35);
        Move::singleton()->perform(ENABLE_SHARPS);
        Move::singleton()->perform(MOVE_BACKWARD,40);
        /*Move::singleton()->perform(MOVE_45ANTICLOCK,4);
        Move::singleton()->perform(MOVE_FORWARD,5);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1.1);
        Move::singleton()->perform(MOVE_FORWARD,45);
        Move::singleton()->perform(MOVE_45ANTICLOCK,2.5);
        Move::singleton()->perform(MOVE_FORWARD,45);
        Move::singleton()->perform(MOVE_45CLOCK,1.5);
        Move::singleton()->perform(MOVE_FORWARD,210);
        Move::singleton()->perform(MOVE_BACKWARD,25);
        Move::singleton()->perform(MOVE_45ANTICLOCK,4.2);
        Move::singleton()->perform(MOVE_FORWARD,90);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1);
        Move::singleton()->perform(MOVE_FORWARD,7);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1);
        Move::singleton()->perform(MOVE_FORWARD,7);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1);
        Move::singleton()->perform(MOVE_FORWARD,7);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1.5);
        Move::singleton()->perform(MOVE_FORWARD,120);*/
        //Verres retour zone de départ
        Move::singleton()->perform(MOVE_45CLOCK,2);
        Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,0.25);
        Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,0.25);
        Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,0.25);
        Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,2);
        Move::singleton()->perform(MOVE_BACKWARD,50);
        Move::singleton()->perform(MOVE_45ANTICLOCK,0.25);
        Move::singleton()->perform(MOVE_BACKWARD,50);
        Move::singleton()->perform(MOVE_45ANTICLOCK,0.25);
        Move::singleton()->perform(MOVE_BACKWARD,50);
        Move::singleton()->perform(MOVE_45ANTICLOCK,0.25);
        Move::singleton()->perform(MOVE_BACKWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,2);
        Move::singleton()->perform(MOVE_FORWARD,30);
        Move::singleton()->perform(MOVE_45CLOCK,2);
        /*Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,0.25);
        Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,0.25);
        Move::singleton()->perform(MOVE_FORWARD,50);
        Move::singleton()->perform(MOVE_45CLOCK,0.25);
        Move::singleton()->perform(MOVE_FORWARD,50);*/

        /*Move::singleton()->perform(MOVE_BACKWARD,25);
        Move::singleton()->perform(MOVE_45ANTICLOCK,4);
        Move::singleton()->perform(MOVE_FORWARD,90);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1);
        Move::singleton()->perform(MOVE_FORWARD,40);
        Move::singleton()->perform(MOVE_45ANTICLOCK,3);
        Move::singleton()->perform(MOVE_FORWARD,125);

        /*Move::singleton()->perform(MOVE_BACKWARD,25);
        Move::singleton()->perform(MOVE_45ANTICLOCK,4.2);
        Move::singleton()->perform(MOVE_FORWARD,120);
        Move::singleton()->perform(MOVE_45ANTICLOCK,1);
        Move::singleton()->perform(MOVE_FORWARD,25);
        Move::singleton()->perform(MOVE_45ANTICLOCK,3.5);
        Move::singleton()->perform(MOVE_FORWARD,150);*/
    }
}
