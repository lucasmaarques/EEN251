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
 */
#include <asf.h>

void inicializacao_UART (void); //protótipo da função

#define CONF_UART              UART0				//seleciona a UART 0
#define CONF_UART_BAUDRATE     115200				// velocidade 115200 bps
#define CONF_UART_CHAR_LENGTH  US_MR_CHRL_8_BIT		// 8 bits de dados
#define CONF_UART_PARITY       US_MR_PAR_NO			// sem paridade
#define CONF_UART_STOP_BITS    US_MR_NBSTOP_1_BIT	// 1 stop bit


void inicializacao_UART (){
	
	 static usart_serial_options_t usart_options = {
		 .baudrate = CONF_UART_BAUDRATE,
		 .charlength = CONF_UART_CHAR_LENGTH,
		 .paritytype = CONF_UART_PARITY,
		 .stopbits = CONF_UART_STOP_BITS
	 };
	
	usart_serial_init((Usart *)CONF_UART, &usart_options); // inicializa a UART
}


int main (void)
{
	unsigned char received_byte;

	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	inicializacao_UART();
	
		usart_serial_putchar((Usart *)CONF_UART, 'A');   // escreve o caracter 'A' no terminal
	
	while(1){
		usart_serial_getchar((Usart *)CONF_UART, &received_byte); //fica travado esperando uma tecla e qdo pressionar armazena tecla em received_byte 
		usart_serial_putchar((Usart *)CONF_UART, received_byte); // ecoa tecla para terminal
	}

}
