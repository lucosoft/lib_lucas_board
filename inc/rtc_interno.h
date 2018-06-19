/*
 * rtc_interno.h
 *
 *  Created on: Jun 19, 2018
 *      Author: Lucas Guerrero
 */

#ifndef RTC_INTERNO_H_
#define RTC_INTERNO_H_

/**
 * @brief	Sets up internal rtc lpc1769
 * @param	Nothing
 * @return	Nothing
 */
void RTC_Init(void);

/**
 * @brief	Handler internal rtc lpc1769
 * @param	Nothing
 * @return	Nothing
 */
void RTC_Funcion(void);

/**
 * @brief	IRQ Handler internal rtc lpc1769
 * @param	Nothing
 * @return	Nothing
 */
void RTC_IRQHandler(void);

#endif /* RTC_INTERNO_H_ */
