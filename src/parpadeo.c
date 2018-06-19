/*
 * parpadeo.c
 *
 *  Created on: Jun 18, 2018
 *      Author: Lucas Guerrero
 */

#include "chip.h"
#include "systick.h"

// Variables
volatile int j=0;							// contador para el delay del parpadeo
volatile int i=0;       					// contador para cambiar de estado
volatile int ciclo = 0;  					// nro de ciclo


void Parpadeo_Sec(void) {
	switch (ciclo) {
	case 0:
		// Cada 1 segundo...
		if (j == 1000) {
			// prender si led estaba apagado o apagar si led estaba prendido
			Board_LED_Toggle(0);
			// reset de la variable contador para el delay
			j = 0;
		}
		break;
	case 1:
		// Cada 500ms...
		if (j == 500) {
			// prender si led estaba apagado o apagar si led estaba prendido
			Board_LED_Toggle(0);
			// reset de la variable contador para el delay
			j = 0;
		}
		break;
	case 2:
		// Cada 500ms...
		if (j == 250) {
			// prender si led estaba apagado o apagar si led estaba prendido
			Board_LED_Toggle(0);
			// reset de la variable contador para el delay
			j = 0;
		}
		break;
	case 3:
		// Cada 500ms...
		if (j == 125) {
			// prender si led estaba apagado o apagar si led estaba prendido
			Board_LED_Toggle(0);
			// reset de la variable contador para el delay
			j = 0;
		}
		break;
	default:
		// reseteo ciclo y los contadores
		ciclo = 0;
		j = 0;
		i = 0;
		break;
	}
}


