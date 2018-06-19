/*
 * pulsador.h
 *
 *  Created on: Jun 18, 2018
 *      Author: Lucas Guerrero
 */

#ifndef PULSADOR_IRQ_H_
#define PULSADOR_IRQ_H_

/**
 * @brief	Configure GPIO interrupt pin, set as pull up and Enable interrupt in the NVIC
 * @param	Nothing
 * @return	Nothing
 */
void Pulsador_Irq_Init(void);

/**
 * @brief	State machine handler the pin interrupt
 * @param	Nothing
 * @return	Nothing
 */
void Pulsador_Irq_Sec(void);

#endif /* PULSADOR_IRQ_H_ */
