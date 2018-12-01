#include "s_debug.h"  
#include "s_usart.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#pragma import(__use_no_semihosting)

struct __FILE 	//��׼����Ҫ��֧�ֺ���  
{ 
	int handle; 
}; 

FILE __stdout;

void _sys_exit(int x) 	//����_sys_exit()�Ա���ʹ�ð�����ģʽ 
{ 
	x = x; 
}

int fputc(int ch, FILE *f)
{ 	
	while(USART_GetFlagStatus(DEBUG_USE_WHICH_UART, USART_FLAG_TXE) == RESET);			//�ȴ��������		
	USART_SendData(DEBUG_USE_WHICH_UART, ch);		    
	return ch;
}

void debug_init(u32 baudrate)
{
	uart_init(DEBUG_USE_WHICH_UART,baudrate);
}

void debug_output(const char* buf,u32 len)
{
	uart_send_data(DEBUG_USE_WHICH_UART, buf, len);
}














