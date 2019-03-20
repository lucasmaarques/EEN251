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
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	inicializacao_UART();
	
	puts("Hello serial."); //puts() escreve a string para o terminal e no final adiciona \n -> nova linha
	printf("teste valor %i", 10);
	puts("Para onde foi?\r");  //\r volta para o início da linha
	
	// usando \r -> carriage return -> volta para o início da linha
	
	puts("Hello serial 2. \r"); //puts() escreve a string para o terminal e no final adiciona \n-> nova linha
	printf("teste valor %i \n\r", 11);
	
	
	while(1){
		
		
		puts("Prontos para terem a vida facilitada novamente? 1: SIM, 2: NAO\r");
		key = getchar(); //usart_serial_getchar((Usart *)CONF_UART, &key); //Alternativa sem o stdio
		switch (key) {
			case '1':
				puts("Ja imaginava.\r");
			break;
			case '2':
				puts("CLAPs.\r");
			break;
			default:
				printf("Opcao nao definida: %d \n\r", key); // imprime o valor decimal da Tabela ASCII do caracter
															// %X fornece o valor em hexa
		}
		
	}

}