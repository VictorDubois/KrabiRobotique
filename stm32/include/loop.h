#ifndef LOOP_H
#define LOOP_H

static long systick_count = 0;

/**@brief fonction externe appellé directement par le microcontroleur à chaque mise à jour. C'est grace à cette fonction que des actions sont exécutés à intervalle régulier */
extern "C" void SysTick_Handler();


#endif // LOOP_H
