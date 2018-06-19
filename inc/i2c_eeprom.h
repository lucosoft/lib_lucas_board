/*
 * i2c_eeprom.h
 *
 *  Created on: Jun 19, 2018
 *      Author: Lucas Guerrero
 */

#ifndef I2C_EEPROM_H_
#define I2C_EEPROM_H_

/**
 * @brief	Initialize pin for I2C1
 * @param	Nothing
 * @return	Nothing
 */
void I2C_Eeprom_Init(void);

/**
 * @brief	Write in I2C1
 * @param	Nothing
 * @return	Nothing
 */
void I2C_Eeprom_Escribir(void);

/**
 * @brief	Read from I2C1
 * @param	Nothing
 * @return	Nothing
 */
void I2C_Eeprom_Leer(void);

#endif /* I2C_EEPROM_H_ */
