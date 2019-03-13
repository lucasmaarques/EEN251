/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#define LED_VERDE (1<<20)// led verde está no PIOA 20
#define BP2 (1 << 3)     // botao BP2 está no PIOB 3

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	PIOA->PIO_PER |= LED_VERDE; // habilita PIOA para controlar pino 20
	PIOA->PIO_OER |= LED_VERDE; // configura pino 20 do PIOA como saída
	PIOB->PIO_PER |= BP2; // habilita PIOA para controlar pino 2
	PIOB->PIO_ODR |= BP2; //Desabilita saída 3 para usar o pino como entrada
	PIOB->PIO_PUER |=BP2; //Liga o PullUp interno no pino 3
	
	/* Insert application code here, after the board has been initialized. */
	
	while(1)
		{
			// O botão do kit vai para zero quando pressionado
			// Acende o led verde quando aperta o botão
			
			if (PIOB->PIO_PDSR & BP2) // verifica se a entrada é '1'
				{
					PIOA->PIO_SODR |= LED_VERDE; // se sim seta a saída em'1' w apaga o led verde
				}
			else PIOA->PIO_CODR |= LED_VERDE;	// caso contrário coloca a saída em '0' e liga o led verde
		}
}
 