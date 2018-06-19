/*
 * pulsador.h
 *
 *  Created on: Jun 18, 2018
 *      Author: Lucas Guerrero
 */

#ifndef PULSADOR_IRQ_H_
#define PULSADOR_IRQ_H_

//#define TICKRATE_HZ1 (1000)	// 1000 ticks per second
//
///* GPIO pin for interrupt */
//#define GPIO_INTERRUPT_PIN     17	/* GPIO pin number mapped to interrupt */
//#define GPIO_INTERRUPT_PORT    GPIOINT_PORT0	/* GPIO port number mapped to interrupt */
//
///* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
//#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
//#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */
//
//// Defines de pulsador
//#define	NO		0  							// Defino pulsador no oprimido
//#define	SI		1  							// Defino pulsador oprimido
//#define	NO_OPRIMIDO		0x00				// Defino estado no oprimido del pulsador
//#define	ESPERA_1		0x01				// Defino estado de espera de finalizacion del transitorio del pulsador
//#define	ESPERA_2		0x02				// Defino estado de espera de finalizacion del transitorio del pulsador
//#define	OPRIMIDO		0x03				// Defino estado de finalizacion del transitorio del pulsador
//#define PB_PORT			GPIOINT_PORT0		// Puerto del pulsador
//#define PB_BIT			GPIO_INTERRUPT_PIN	// Bit del pulsador
//#define DELAY_PULSADOR	30					// Tiempo de espera de finalizacion del transitorio del pulsador [ms]


void Pulsador_Irq_Init(void);
void Pulsador_Irq_Sec(void);

//void Parpadeo_Sec(void);

#endif /* PULSADOR_IRQ_H_ */
