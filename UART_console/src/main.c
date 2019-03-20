/**
 *	UART 
 * 
 *
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 *   - OBS PROCURE por stdio.h para entender as funções puts(,) printf() e getchar() 
 */
#include <asf.h>
#include "string.h"  //se quiser manipular strings

void inicializacao_UART (void); //protótipo da função

#define CONF_UART              UART0				//utilizando UART 0
#define CONF_UART_BAUDRATE     115200				// 115200 bps
#define CONF_UART_CHAR_LENGTH  US_MR_CHRL_8_BIT		// dados de 8 bits
#define CONF_UART_PARITY       US_MR_PAR_NO			//sem paridade
#define CONF_UART_STOP_BITS    US_MR_NBSTOP_1_BIT	// 1 stop bit
#define LED_VERDE (1<<20) // o led verde está ligado no PA20
#define LED_AZUL (1<<19)  // led azul está ligado no PA19



void inicializacao_UART (void){
	
	 static usart_serial_options_t usart_options = {
		 .baudrate = CONF_UART_BAUDRATE,
		 .charlength = CONF_UART_CHAR_LENGTH,
		 .paritytype = CONF_UART_PARITY,
		 .stopbits = CONF_UART_STOP_BITS
	 };
	
	usart_serial_init((Usart *)CONF_UART, &usart_options);
	
	stdio_serial_init((Usart *)CONF_UART, &usart_options);
}


int main (void)
{
	//unsigned char received_byte;
	unsigned char key;
	int contaTeclaA = 0;
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	PIOA->PIO_PER |= LED_AZUL | LED_VERDE;//  habilita PIOA 19 e 20 (leds)
	PIOA->PIO_OER |= LED_AZUL | LED_VERDE; //configura PIOA 19 e 20 como saídas
	
	inicializacao_UART();
	
	//puts("Hello serial."); //puts() escreve a string para o terminal e no final adiciona \n -> nova linha
	//printf("teste valor %i", 10);
	//puts("Para onde foi?\r");  //\r volta para o início da linha
	//
	//// usando \r -> carriage return -> volta para o início da linha
	//
	//puts("Hello serial 2. \r"); //puts() escreve a string para o terminal e no final adiciona \n-> nova linha
	//printf("teste valor %i \n\r", 11);

	puts("Programa AG - Digite 1 para abrir as opções");
	while(1){
		
		//FAZER ACENDER E APAGAR A LUZ DE ACORDO COM O CODIGO - corrigir para ASF
		key = getchar(); //usart_serial_getchar((Usart *)CONF_UART, &key); //Alternativa sem o stdio
		switch (key) {
			case '1':
			puts("\nAperte:\n2 para acender a luz verde\n3 para acender a luz azul\n4 para apagar a luz verde\n5 para apagar a luz azul\n\r");
			break;
			case '2':
			PIOA->PIO_CODR |= LED_VERDE;  //zera saída PA20--> acende led verde 
				puts("\nLUZ VERDE\r");
			break;
			case '4':
			PIOA->PIO_SODR |= LED_VERDE;
			puts("\nLUZ VERDE APAGADA\r");
			break;
			case '5':
			PIOA->PIO_SODR |= LED_AZUL;
			puts("\nLUZ AZUL APAGADA\r");
			break;
			case '3':
			PIOA->PIO_CODR |= LED_AZUL;	  //zera saída PA19--> acende led azul
			puts("\nLUZ AZUL\r");
			break;
			case 'A':
				contaTeclaA++;
				printf("\nOk\n\r");
			break;
			case 'R':
				printf("\nAcionamentos:%04i\n\r",contaTeclaA);
			break;
			default:
				printf("\nOpcao nao definida\n"); // imprime o valor decimal da Tabela ASCII do caracter
															// %X fornece o valor em hexa
		}
		
	}

}