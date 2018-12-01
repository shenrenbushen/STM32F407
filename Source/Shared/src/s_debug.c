#include "s_debug.h"  
#include "s_usart.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#pragma import(__use_no_semihosting)

struct __FILE 	//标准库需要的支持函数  
{ 
	int handle; 
}; 

FILE __stdout;

void _sys_exit(int x) 	//定义_sys_exit()以避免使用半主机模式 
{ 
	x = x; 
}

int fputc(int ch, FILE *f)
{ 	
	while(USART_GetFlagStatus(DEBUG_USE_WHICH_UART, USART_FLAG_TXE) == RESET);			//等待发送完毕		
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














