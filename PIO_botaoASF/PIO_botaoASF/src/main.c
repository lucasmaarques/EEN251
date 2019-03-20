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
#define LED_VERDE IOPORT_CREATE_PIN(PIOA,20) // led verde est� no pino 20 do PIOA
//ou
//#define LED_VERDE IOPORT_CREATE_PIN(PIOA,PIO_PA20_IDX) // j� tem um define no Sam4s_ek2.h
#define BP2 IOPORT_CREATE_PIN(PIOB,3) // bota� est� no pino 3 do PIOB
//ou
//#define BP2 IOPORT_CREATE_PIN(PIOB,PIO_PA3_IDX)// j� tem um define no Sam4s_ek2.h


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	//bool valor; //para usar com solu��o 2
	
	sysclk_init();
	board_init();
	ioport_init(); //inicializa o servi�o IOPORT
	ioport_enable_pin(LED_VERDE) ; // habilita led verde no PIO
	ioport_enable_pin(BP2);        // habilita bot�o no PIO
	ioport_set_pin_dir(LED_VERDE,IOPORT_DIR_OUTPUT); // LED como sa�da
	ioport_set_pin_dir(BP2,IOPORT_DIR_INPUT);  // bot�o como entrada
	ioport_set_pin_mode(BP2,IOPORT_MODE_PULLUP); // para habilitar outros modos basta fazer ou l�gico |)
	

	/* Insert application code here, after the board has been initialized. */
	int estadoSaida = 0;
	int estadoEntrada = ioport_get_pin_level(BP2);
	while(1)
	{
		if(estadoEntrada != ioport_get_pin_level(BP2)){
			estadoEntrada = ioport_get_pin_level(BP2);
			if(!estadoEntrada)
				estadoSaida = !estadoSaida;
			
		}
		//if(ioport_get_pin_level(BP2)) ioport_set_pin_level(LED_VERDE,1); // pode se usar TRUE
		//else ioport_set_pin_level(LED_VERDE,0); //pode se usar FALSE
		if(estadoSaida) ioport_set_pin_level(LED_VERDE,1); // pode se usar TRUE
		else ioport_set_pin_level(LED_VERDE,0); //pode se usar FALSE
	} 
	
	/* solu��o 2. Outra solu��o poss�vel
	while(1)
	{
		valor = ioport_get_pin_level(BP2); // l� valor
		ioport_set_pin_level(LED_VERDE,valor); //transfere valor para o pino
	} */
}

// Obs: para inverter o valor de um pino, a API IOPORT possui a fun��o ioport_toggle_pin_level (ioport_pin_t pin)
// para v�rios pinos em um mesmo port: ioport_toggle_port_level (ioport_port_t port, ioport_port_mask_t mask)
