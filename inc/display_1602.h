/*
 * display_1602.h
 *
 *  Created on: Jun 19, 2018
 *      Author: Lucas Guerrero
 */

#ifndef DISPLAY_1602_H_
#define DISPLAY_1602_H_

/* Prototipos de funciones */
void LCD_Init(void);
void LCD_SendNibble(uint8_t theNibble);
void LCD_SendChar(char theChar);
void LCD_SendInstruction(uint8_t theInstruction);
void LCD_SendByte(uint8_t theByte);
void LCD_GoToxy(uint8_t x, uint8_t y);
void LCD_Print(char *p);
void LCD_create_char(uint8_t, uint8_t*);
void LCD_Shift(const uint8_t, const uint8_t); //SC 0-C / 1-S   //LR 0-L / 1-R
void LCD_Home();
void LCD_Clrscr();

// Funciones necesarias para los delays
void LCD_usDelay(uint32_t usec);
void LCD_Tim1Init(void);
void LCD_Tim1DeInit(void);

// Inicializacion de los pines de conexion
void RS_PIN_INIT(int, int);
void EN_PIN_INIT(int, int);
void D4_PIN_INIT(int, int);
void D5_PIN_INIT(int, int);
void D6_PIN_INIT(int, int);
void D7_PIN_INIT(int, int);

#endif /* DISPLAY_1602_H_ */
