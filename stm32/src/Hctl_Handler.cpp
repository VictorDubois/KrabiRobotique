#include "Hctl_Handler.h"

Hctl_Handler::Hctl_Handler()
{
    // propager horloge au port C
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // initialiser pins d'entrÃ©e sur le STM
    GPIO_InitTypeDef GPIO_InitStructureEntreesPortC;
    GPIO_InitStructureEntreesPortC.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructureEntreesPortC.GPIO_Mode = GPIO_Mode_IN_FLOATING;         // Le mode entrÃ©e Input floating (fil simple)
    GPIO_InitStructureEntreesPortC.GPIO_Speed = GPIO_Speed_50MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructureEntreesPortC);

    GPIO_InitTypeDef GPIO_InitStructureEntreesPortB;
    GPIO_InitStructureEntreesPortB.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_15;
    GPIO_InitStructureEntreesPortB.GPIO_Mode = GPIO_Mode_IN_FLOATING;         // Le mode entrÃ©e Input floating (fil simple)
    GPIO_InitStructureEntreesPortB.GPIO_Speed = GPIO_Speed_50MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructureEntreesPortB);

    //initialiser pins de sortie
    GPIO_InitTypeDef GPIO_InitStructureSorties;
    GPIO_InitStructureSorties.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructureSorties.GPIO_Mode = GPIO_Mode_Out_PP;    // Output PUSH PULL
    GPIO_InitStructureSorties.GPIO_Speed = GPIO_Speed_50MHz;        //La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructureSorties);

    // envoyer RST1 et 2
    GPIO_WriteBit(GPIOC,GPIO_Pin_10,Bit_RESET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_11,Bit_RESET);

    //for(int lol=0;lol<5000;lol++);

    while(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_11) != Bit_SET && GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_10) != Bit_SET);  // on attend que ce soit bien remis à zero

    GPIO_WriteBit(GPIOC,GPIO_Pin_10,Bit_SET);   // on laisse pas Ã©ternellement le RST Ã  1...
    GPIO_WriteBit(GPIOC,GPIO_Pin_11,Bit_SET);

    // SÃ©lectionner mode 1x
    GPIO_WriteBit(GPIOC,GPIO_Pin_8,Bit_SET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_SET);

    // Envoyer OE
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);
}

Hctl_Handler::~Hctl_Handler()
{
    // ArrÃªter l'OE
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);

    // Envoyer RST
    GPIO_WriteBit(GPIOC,GPIO_Pin_8,Bit_SET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_SET);   // pas la peine d'arrÃªter d'envoyer Vdd puisqu'on Ã©teint le robot.

}

uint32_t Hctl_Handler::reconstituerCompteur(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    a <<= 8*3;
    b <<= 8*2;
    c <<= 8;

    return (a+b+c+d);
}

uint8_t Hctl_Handler::reconstituerOctet(uint8_t a, uint8_t b, uint8_t c, uint8_t d,  uint8_t e,  uint8_t f,  uint8_t g,  uint8_t h)
{
    a <<= 7;
    b <<= 6;
    c <<= 5;
    d <<= 4;
    e <<= 3;
    f <<= 2;
    g <<= 1;

    return (a+b+c+d+e+f+g+h);
}

uint8_t Hctl_Handler::Pina(){
    uint8_t h = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
    uint8_t g = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    uint8_t f = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
    uint8_t e = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);

    uint8_t d = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
    uint8_t c = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
    uint8_t b = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
    uint8_t a = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);

    return reconstituerOctet(h,g,f,e,d,c,b,a);
}

uint8_t Hctl_Handler::Get_hi(){

    for(int a = 0; a < HCTL_BCL; a++);
    uint8_t Hi_old = Pina();
   /* uint8_t Hi_new = Pina();
    if( Hi_new == Hi_old ){
        return Hi_new;
    }
    else return Get_hi(); */

    return Hi_old;
}

uint32_t Hctl_Handler::regarderRoue(BitAction valeurPinXY){

    GPIO_WriteBit(GPIOC, GPIO_Pin_4, valeurPinXY);    // on sélectionne la roue

    GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);        // on met l'OE en valeur basse pour pouvoir lire le compteur
    for(int a = 0; a < HCTL_BCL; a++);

    /**D4 : bit de poids fort*/
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);

    GPIO_WriteBit(GPIOC, GPIO_Pin_5, Bit_RESET);

    /*uint8_t h4 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
    uint8_t g4 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    uint8_t f4 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
    uint8_t e4 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);

    uint8_t d4 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
    uint8_t c4 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
    uint8_t b4 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
    uint8_t a4 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);*/
    uint8_t D4 = Get_hi();


    /**D3*/
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);

    /*uint8_t h3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
    uint8_t g3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    uint8_t f3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
    uint8_t e3 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);

    uint8_t d3 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
    uint8_t c3 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
    uint8_t b3 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
    uint8_t a3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);*/

    uint8_t D3 = Get_hi();

    /**D2*/
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);

    /*uint8_t h2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
    uint8_t g2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    uint8_t f2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
    uint8_t e2 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);

    uint8_t d2 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
    uint8_t c2 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
    uint8_t b2 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
    uint8_t a2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);*/

    uint8_t D2 = Get_hi();

    /**D1 : bit de poids faible*/
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);

    /*uint8_t h1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
    uint8_t g1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    uint8_t f1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
    uint8_t e1 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);

    uint8_t d1 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
    uint8_t c1 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
    uint8_t b1 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
    uint8_t a1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);*/

    uint8_t D1 = Get_hi();

    GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);    // on remet l'OE en valeur haute pour que le compteur soit MàJ
    for(int a = 0; a < HCTL_BCL; a++);

    /*uint8_t D1 = reconstituerOctet(h1,g1,f1,e1,d1,c1,b1,a1);
    uint8_t D2 = reconstituerOctet(h2,g2,f2,e2,d2,c2,b2,a2);
    uint8_t D3 = reconstituerOctet(h3,g3,f3,e3,d3,c3,b3,a3);
    uint8_t D4 = reconstituerOctet(h4,g4,f4,e4,d4,c4,b4,a4);*/

    return reconstituerCompteur(D4,D3,D2,D1);
}

ValeursRoues Hctl_Handler::faireUnTour() {
    for(;;) {
        uint32_t a = 0;
        uint32_t b = 4;
        a = regarderRoue(Bit_SET);

        uint8_t etatPC10 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_10);
        uint8_t etatPC11 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_11);

        b = regarderRoue(Bit_RESET);
        roues.setRoueGauche(a);
        roues.setRoueDroite(b);

        etatPC10 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_10);
        etatPC11 = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_11);
    }
        return roues;
}
