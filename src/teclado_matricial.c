/*
 * teclado_matricial.c
 *
 *  Created on: Jun 19, 2018
 *      Author: Lucas Guerrero
 */

/*
 * Teclado.c
 *
 *  Created on: 4/2/2016
 *      Author: Santiago
 */
#include "board.h"
//#include "GPIO.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

//Definiciones
#define	TECLADO_COLUMNA1_PORT	0
#define	TECLADO_COLUMNA1_BIT	21
#define	TECLADO_COLUMNA2_PORT	0
#define	TECLADO_COLUMNA2_BIT	3
#define	TECLADO_COLUMNA3_PORT	0
#define	TECLADO_COLUMNA3_BIT	27
#define	TECLADO_COLUMNA4_PORT	0
#define	TECLADO_COLUMNA4_BIT	28

#define	TECLADO_FILA1_PORT		0
#define	TECLADO_FILA1_BIT		24
#define	TECLADO_FILA2_PORT		0
#define	TECLADO_FILA2_BIT		25
#define	TECLADO_FILA3_PORT		0
#define	TECLADO_FILA3_BIT		26
#define	TECLADO_FILA4_PORT		1
#define	TECLADO_FILA4_BIT		30

#define TECLADO_BUZZER_PORT		0
#define TECLADO_BUZZER_BIT		7

#define TECLA1		0x0001	//1
#define TECLA2		0x0002	//2
#define TECLA3		0x0004	//3
#define TECLA4		0x0008	//A
#define TECLA5		0x0010	//4
#define TECLA6		0x0020	//5
#define TECLA7		0x0040	//6
#define TECLA8		0x0080	//B
#define TECLA9		0x0100	//7
#define TECLA10		0x0200	//8
#define TECLA11		0x0400	//9
#define TECLA12		0x0800	//C
#define TECLA13		0x1000	//*
#define TECLA14		0x2000	//0
#define TECLA15		0x4000	//#
#define TECLA16		0x8000	//D

#define BUZZER_PULSE	20

#define OUTPUT	true
#define INPUT 	false

volatile int Teclas = 0, TeclasAnterior = 0, TeclaPresionada = 0, TiempoPresionado = 0, buzz=0;
volatile bool Presionado = false, PresionLarga = false;

static void Fila1_on()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA1_PORT, TECLADO_FILA1_BIT, 0);
}

static void Fila1_off()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA1_PORT, TECLADO_FILA1_BIT, 1);
}

static void Fila2_on()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA2_PORT, TECLADO_FILA2_BIT, 0);
}

static void Fila2_off()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA2_PORT, TECLADO_FILA2_BIT, 1);
}

static void Fila3_on()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA3_PORT, TECLADO_FILA3_BIT, 0);
}

static void Fila3_off()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA3_PORT, TECLADO_FILA3_BIT, 1);
}

static void Fila4_on()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA4_PORT, TECLADO_FILA4_BIT, 0);
}

static void Fila4_off()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_FILA4_PORT, TECLADO_FILA4_BIT, 1);
}

static int Columna1()
{
	if (!Chip_GPIO_GetPinState(LPC_GPIO, TECLADO_COLUMNA1_PORT, TECLADO_COLUMNA1_BIT))
		return 1;
	else
		return 0;
}

static int Columna2()
{
	if (!Chip_GPIO_GetPinState(LPC_GPIO, TECLADO_COLUMNA2_PORT, TECLADO_COLUMNA2_BIT))
		return 1;
	else
		return 0;
}

static int Columna3()
{
	if (!Chip_GPIO_GetPinState(LPC_GPIO, TECLADO_COLUMNA3_PORT, TECLADO_COLUMNA3_BIT))
		return 1;
	else
		return 0;
}

static int Columna4()
{
	if (!Chip_GPIO_GetPinState(LPC_GPIO, TECLADO_COLUMNA4_PORT, TECLADO_COLUMNA4_BIT))
		return 1;
	else
		return 0;
}

static void Teclado_Tim0Init(void) {

#ifdef BOARD_NXP_XPRESSO_11C24

	Chip_TIMER_Init(LPC_TIMER16_0);
	Chip_TIMER_PrescaleSet(LPC_TIMER16_0,
			Chip_Clock_GetSystemClockRate() / 1000 - 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_0, 0);
	Chip_TIMER_StopOnMatchDisable(LPC_TIMER16_0, 0);

	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, 100);

	NVIC_ClearPendingIRQ(TIMER_16_0_IRQn);
	NVIC_EnableIRQ(TIMER_16_0_IRQn);

	Chip_TIMER_Enable(LPC_TIMER16_0);
#endif

#ifdef BOARD_NXP_LPCXPRESSO_1769

	uint32_t timerFreq;

	/* Enable timer 1 clock */
		Chip_TIMER_Init(LPC_TIMER0);

		/* Timer rate is system clock rate */
		timerFreq = Chip_Clock_GetSystemClockRate();

		/* Timer setup for match and interrupt at TICKRATE_HZ */
		Chip_TIMER_Reset(LPC_TIMER0);
		Chip_TIMER_PrescaleSet(LPC_TIMER0,
		Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER0) / 1000000 - 1);
		Chip_TIMER_MatchEnableInt(LPC_TIMER0, 1);
//		Chip_TIMER_SetMatch(LPC_TIMER0, 1, (timerFreq / TICKRATE_HZ1));
		Chip_TIMER_SetMatch(LPC_TIMER0, 1, 1000);
		Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 1);
		Chip_TIMER_Enable(LPC_TIMER0);

		/* Enable timer interrupt */
		NVIC_ClearPendingIRQ(TIMER0_IRQn);
		NVIC_EnableIRQ(TIMER0_IRQn);

#endif


}


static void Teclado_Tim0DeInit(void) {

#ifdef BOARD_NXP_XPRESSO_11C24
	Chip_TIMER_Disable(LPC_TIMER16_0);
	NVIC_DisableIRQ(TIMER_16_0_IRQn);

#endif

#ifdef  BOARD_NXP_LPCXPRESSO_1769

#endif
}

static void Teclado_Fila (int Fila)
{
	Fila1_off();
	Fila2_off();
	Fila3_off();
	Fila4_off();

	switch (Fila)
	{
		case 1:
		{
			Fila1_on();
			break;
		}
		case 2:
		{
			Fila2_on();
			break;
		}
		case 3:
		{
			Fila3_on();
			break;
		}
		case 4:
		{
			Fila4_on();
			break;
		}
		default:
			break;
	}
}

static int Teclado_Columna()
{
	return ((Columna4() << 3) | (Columna3() << 2) | (Columna2() << 1) | (Columna1()));
}

#ifdef BOARD_NXP_XPRESSO_11C24

void TIMER16_0_IRQHandler(void) {
	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, 0)) {

#endif

#ifdef  BOARD_NXP_LPCXPRESSO_1769

void TIMER0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);
		Board_LED_Toggle(0);

#endif


		TeclasAnterior = Teclas;
		Teclas = 0;
		Teclado_Fila(1);
		Teclas = Teclado_Columna();
		Teclado_Fila(2);
		Teclas += (Teclado_Columna() << 4);
		Teclado_Fila(3);
		Teclas += (Teclado_Columna() << 8);
		Teclado_Fila(4);
		Teclas += (Teclado_Columna() << 12);
		Teclado_Fila(0);

		if (Presionado)
			TiempoPresionado++;

		if (Teclas != TeclasAnterior)
		{
			if (Teclas == 0)
			{
				Presionado = false;
				TeclaPresionada = TeclasAnterior;
				buzz = BUZZER_PULSE;

				if (TiempoPresionado>30)
					PresionLarga = true;

				TiempoPresionado = 0;
			}
			else
				Presionado = true;
		}
//		if (buzz>0)
//		{
//			Buzzer_on();
//			buzz--;
//		}
//		else
//			Buzzer_off();


}

#ifdef BOARD_NXP_XPRESSO_11C24

		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);
#endif

#ifdef  BOARD_NXP_LPCXPRESSO_1769

#endif
}


void Teclado_Init ()
{
	Teclado_Tim0Init();

	PIN_INIT(TECLADO_BUZZER_PORT, TECLADO_BUZZER_BIT, OUTPUT);

	PIN_INIT(TECLADO_COLUMNA1_PORT, TECLADO_COLUMNA1_BIT, INPUT);
	PIN_INIT(TECLADO_COLUMNA2_PORT, TECLADO_COLUMNA2_BIT, INPUT);
	PIN_INIT(TECLADO_COLUMNA3_PORT, TECLADO_COLUMNA3_BIT, INPUT);
	PIN_INIT(TECLADO_COLUMNA4_PORT, TECLADO_COLUMNA4_BIT, INPUT);

	PIN_INIT(TECLADO_FILA1_PORT, TECLADO_FILA1_BIT, OUTPUT);
	PIN_INIT(TECLADO_FILA2_PORT, TECLADO_FILA2_BIT, OUTPUT);
	PIN_INIT(TECLADO_FILA3_PORT, TECLADO_FILA3_BIT, OUTPUT);
	PIN_INIT(TECLADO_FILA4_PORT, TECLADO_FILA4_BIT, OUTPUT);

	Fila1_off();
	Fila2_off();
	Fila3_off();
	Fila4_off();
}

int Teclado_Presionado ()
{
	int aux=0;
	aux = TeclaPresionada;
	TeclaPresionada = 0;
	switch (aux) {
		case 0:
			return 0;
			break;
		case 1<<0:
		case 1<<1:
		case 1<<2:
		case 1<<3:
		case 1<<4:
		case 1<<5:
		case 1<<6:
		case 1<<7:
		case 1<<8:
		case 1<<9:
		case 1<<10:
		case 1<<11:
		case 1<<12:
		case 1<<13:
		case 1<<14:
		case 1<<15:
		{
			return aux;
			break;
		}
		default:
			return -1;
			break;
	}
	return aux;
}

bool Teclado_Presion_Larga()
{
	if (PresionLarga)
	{
		PresionLarga = false;
		return true;
	}
	else
		return false;
}

void Buzzer_on()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_BUZZER_PORT, TECLADO_BUZZER_BIT, 1);
}

void Buzzer_off()
{
	Chip_GPIO_WritePortBit(LPC_GPIO, TECLADO_BUZZER_PORT, TECLADO_BUZZER_BIT, 0);
}

void PIN_INIT(int port, int bit, bool dir) {

#ifdef BOARD_NXP_XPRESSO_11C24

	switch (port) {
	case 0: {
		switch (bit) {
		case 0:			//Reset
			break;
		case 1: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_1, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 2: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_2, IOCON_FUNC0);
			break;
		}
		case 3: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_3, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 4: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_4, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 5: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_5, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 6: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_6, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 7: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_7, IOCON_FUNC0);
			break;
		}
		case 8: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_8, IOCON_FUNC0);
			break;
		}
		case 9: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_9, IOCON_FUNC0);
			break;
		}
		case 10:		//SWCLK 1115
			break;
		case 11: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_11, IOCON_FUNC1);
			break;
		}
		default:
			break;
		}
		break;
	}
	case 1: {
		switch (bit) {
		case 0: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_0, IOCON_FUNC1);
			break;
		}
		case 1: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_1, IOCON_FUNC1);
			break;
		}
		case 2: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_2, IOCON_FUNC1);
			break;
		}
		case 3:		//SWDIO 1115
			break;
		case 4: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_4, IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGMODE_EN);
			break;
		}
		case 5: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_5, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 6: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, IOCON_FUNC0);
			break;
		}
		case 7: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, IOCON_FUNC0);
			break;
		}
		case 8: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_8, IOCON_FUNC0 | IOCON_MODE_PULLUP);
			break;
		}
		case 9: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_9, IOCON_FUNC0);
			break;
		}
		case 10: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_10, IOCON_FUNC0);
		}
			break;
		case 11: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_11, IOCON_FUNC0);
		}
			break;
		default:
			break;
		}
		break;
	}
	case 2: {
		switch (bit) {
		case 0: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_0, IOCON_FUNC0);
			break;
		}
		case 1: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_1, IOCON_FUNC0);
			break;
		}
		case 2: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_2, IOCON_FUNC0);
			break;
		}
		case 3: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_3, IOCON_FUNC0);
			break;
		}
		case 4: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_4, IOCON_FUNC0);
			break;
		}
		case 5: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_5, IOCON_FUNC0);
			break;
		}
		case 6: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_6, IOCON_FUNC0);
			break;
		}
		case 7: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_7, IOCON_FUNC0);
			break;
		}
		case 8: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_8, IOCON_FUNC0);
			break;
		}
		case 9: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_9, IOCON_FUNC0);
			break;
		}
		case 10: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_10, IOCON_FUNC0);
			break;
		}
		case 11: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_11, IOCON_FUNC0);
			break;
		}
		default:
			break;
		}
		break;
	}
	case 3: {
		switch (bit) {
		case 0: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_0, IOCON_FUNC0);
			break;
		}
		case 1: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_1, IOCON_FUNC0);
			break;
		}
		case 2: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_2, IOCON_FUNC0);
			break;
		}
		case 3: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_3, IOCON_FUNC0);
			break;
		}
		case 4: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_4, IOCON_FUNC0);
			break;
		}
		case 5: {
			Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO3_5, IOCON_FUNC0);
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

#endif

//	Chip_IOCON_PinMux(LPC_GPIO, port, bit,IOCON_MODE_PULLUP, IOCON_FUNC0);
	Chip_GPIO_SetPinDIR(LPC_GPIO, port, bit, dir);
}

