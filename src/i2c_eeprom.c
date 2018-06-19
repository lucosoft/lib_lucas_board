/*
 * i2c_eeprom.c
 *
 *  Created on: Jun 19, 2018
 *      Author: Lucas Guerrero
 */

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
uint8_t wbuf[5] = {0,0,0x55,0x44,0x33};
uint8_t rbuf[3] = {0,0,0};
//uint32_t i;
I2C_XFER_T xfer;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void I2C_Eeprom_Init(void) {

	Chip_I2C_SetClockRate(I2C1, 100000);
	Chip_I2C_SetMasterEventHandler(I2C1, Chip_I2C_EventHandlerPolling);
	Chip_I2C_Init(I2C1);
	Board_I2C_Init(I2C1);
}

void I2C_Eeprom_Escribir(void) {

	int dato;
	/* Transferencia de escritura (escribo addr y datos, ojo, tamaño de página 32 bytes) */
	xfer.rxBuff = 0;
	xfer.rxSz = 0;
	xfer.slaveAddr = 0x50;
	xfer.status = 0;
	xfer.txBuff = wbuf;
	xfer.txSz = 5;

	dato = Chip_I2C_MasterTransfer(I2C1, &xfer);

	//delay por software calculado con el teorema de los cinco dedos oscilantes
	for (int i = 0; i < 0xFFFF; i++);
}

void I2C_Eeprom_Leer(void) {
	/* Transferencia de lectura (escribo addr, leo datos) */
	xfer.rxBuff = rbuf;
	xfer.rxSz = 3;
	xfer.slaveAddr = 0x50;
	xfer.status = 0;
	xfer.txBuff = wbuf;
	xfer.txSz = 2;
	Chip_I2C_IsMasterActive(I2C1);
	Chip_I2C_MasterTransfer(I2C1, &xfer);

	//delay por software calculado con el teorema de los cinco dedos oscilantes
	for (int i = 0; i < 0xFFFF; i++);
}
