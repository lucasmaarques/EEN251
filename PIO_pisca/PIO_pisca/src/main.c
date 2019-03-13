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
#define LED_VERDE (1<<20) // o led verde está ligado no PA20
#define LED_AZUL (1<<19)  // led azul está ligado no PA19


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	PIOA->PIO_PER |= LED_AZUL | LED_VERDE;//  habilita PIOA 19 e 20 (leds)
	PIOA->PIO_OER |= LED_AZUL | LED_VERDE; //configura PIOA 19 e 20 como saídas

	/* Insert application code here, after the board has been initialized. */
	
	// loop infinito
	
	while(1){
		//PISCA leds verde e azul de maneira alternada. 
		// O led acende colocando 0 no pino. Ver manual do kit 
		
		PIOA->PIO_CODR |= LED_VERDE;  //zera saída PA20--> acende led verde
		PIOA->PIO_SODR |= LED_AZUL;   // coloca 1 na saída PA19 --> apaga led azul
		delay_ms(500);				  // atraso de 500ms 
		PIOA->PIO_CODR |= LED_AZUL;	  //zera saída PA19--> acende led azul
		PIOA->PIO_SODR |= LED_VERDE;  //coloca 1 na saída PA20 --> apaga led verde
		delay_ms(500);				  // periodo total de 1ms, fornecendo frequência de 1Hz piscando
			
	}
}
