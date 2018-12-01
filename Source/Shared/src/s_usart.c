#include "s_usart.h"  


/*--------------------------------------------
note:串口初始化
--------------------------------------------*/
void uart_init(USART_TypeDef* USARTx, INT32U baud)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	
	if(USARTx == USART1)												
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 			//GPIOA9与GPIOA10
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOA,&GPIO_InitStructure); 												//初始化PA9，PA10	

		USART_InitStructure.USART_BaudRate = baud;										//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART1, &USART_InitStructure); 																				//初始化串口1	
			
		USART_Cmd(USART1, ENABLE);  																	//使能串口1
		
		USART_ClearFlag(USART1, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//清除中断标志位
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);								//开启相关中断（USART_IT_TC、USART_IT_TXE、USART_IT_RXNE）

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;							//串口1中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);																//根据指定的参数初始化VIC寄存器			
	}
	
	if(USARTx == USART2)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		
		
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; 				//GPIOA2与GPIOA3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOA,&GPIO_InitStructure); 												//初始化PA2，PA3		
		
		USART_InitStructure.USART_BaudRate = baud;										//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART2, &USART_InitStructure); 																				//初始化串口2	

		USART_Cmd(USART2, ENABLE);  																	//使能串口2
		
		USART_ClearFlag(USART2, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//清除中断标志位
		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);								//开启相关中断（USART_IT_TC、USART_IT_TXE、USART_IT_RXNE）

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;							//串口2中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);																//根据指定的参数初始化VIC寄存器			
	}	

	if(USARTx == USART3)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);		
		
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); 
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 			//GPIOB10与GPIOB11
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOB,&GPIO_InitStructure); 												//初始化PB10，PB11		
		
		USART_InitStructure.USART_BaudRate = baud;										//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART3, &USART_InitStructure); 																				//初始化串口3	

		USART_Cmd(USART3, ENABLE);  																	//使能串口3
		
		USART_ClearFlag(USART3, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//清除中断标志位
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);								//开启相关中断（USART_IT_TC、USART_IT_TXE、USART_IT_RXNE）

		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;							//串口3中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);																//根据指定的参数初始化VIC寄存器			
	}	
	
	if(USARTx == UART4)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);		
		
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); 
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 			//GPIOC10与GPIOC11
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOC,&GPIO_InitStructure); 												//初始化PC10，PC11		
		
		USART_InitStructure.USART_BaudRate = baud;										//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(UART4, &USART_InitStructure); 																					//初始化串口4	

		USART_Cmd(UART4, ENABLE);  																		//使能串口4
		
		USART_ClearFlag(UART4, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);					//清除中断标志位
		USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);								//开启相关中断（USART_IT_TC、USART_IT_TXE、USART_IT_RXNE）

		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;							//串口4中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);																//根据指定的参数初始化VIC寄存器			
	}	


	if(USARTx == UART5)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);		
		
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART4); 
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART4); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 										//GPIOC12
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOC,&GPIO_InitStructure); 												//初始化PC12		
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 										//GPIOD2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOD,&GPIO_InitStructure); 												//初始化PD2				
		
		USART_InitStructure.USART_BaudRate = baud;										//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(UART5, &USART_InitStructure); 																					//初始化串口5	

		USART_Cmd(UART5, ENABLE);  																		//使能串口5
		
		USART_ClearFlag(UART5, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);					//清除中断标志位
		USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);								//开启相关中断（USART_IT_TC、USART_IT_TXE、USART_IT_RXNE）

		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;							//串口5中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);																//根据指定的参数初始化VIC寄存器			
	}

	if(USARTx == USART6)												
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	 
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6); 
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 				//GPIOC6与GPIOC7
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//上拉
		GPIO_Init(GPIOC,&GPIO_InitStructure); 												//初始化PC6，PC7	

		USART_InitStructure.USART_BaudRate = baud;										//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART6, &USART_InitStructure); 																				//初始化串口6	
			
		USART_Cmd(USART6, ENABLE);  																	//使能串口6
		
		USART_ClearFlag(USART6, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//清除中断标志位
		USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);								//开启相关中断（USART_IT_TC、USART_IT_TXE、USART_IT_RXNE）

		NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;							//串口6中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);																//根据指定的参数初始化VIC寄存器			
	}	
}



/*--------------------------------------------
note:串口发送
--------------------------------------------*/
INT8U uart_send_data(USART_TypeDef* USARTx, const char* buf, INT32U len)
{
	INT32U cycle = 0;
	if(USARTx == USART1)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);			//等待发送完毕		
			USART_SendData(USART1, *(buf+cycle));		
		}
	}
	
	if(USARTx == USART2)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);			//等待发送完毕		
			USART_SendData(USART2, *(buf+cycle));		
		}
	}	
	
	if(USARTx == USART3)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);			//等待发送完毕		
			USART_SendData(USART3, *(buf+cycle));		
		}
	}
	
	if(USARTx == UART4)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);				//等待发送完毕		
			USART_SendData(UART4, *(buf+cycle));		
		}
	}	
	
	if(USARTx == UART5)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);				//等待发送完毕		
			USART_SendData(UART5, *(buf+cycle));		
		}
	}	

	if(USARTx == USART6)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);			//等待发送完毕		
			USART_SendData(USART6, *(buf+cycle));		
		}
	}	
	return 0;
}







