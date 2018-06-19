/*
 * systick.c
 *
 *  Created on: Jun 18, 2018
 *      Author: Lucas Guerrero
 */

#include "chip.h"

extern volatile int j;
extern volatile int pulsador_tick;


void SysTick_Handler(void) {

	// incremento la variable contador para el delay
	j++;

#if defined(PULSADOR_IRQ)

	if(pulsador_tick>0){
		pulsador_tick--;
	}
#else
	// incremento la variable contador para cambiar de estado
	i++;
	//Cambio de ciclo cada 3 segundos
	if(i==3000){
		//reseteo los contadores
		i=0;
		j=0;
		// incremento el ciclo
		ciclo++;
		if(ciclo==4)ciclo=0;
		}
#endif



}
