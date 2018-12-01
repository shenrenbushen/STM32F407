#include "s_usart.h"  


/*--------------------------------------------
note:���ڳ�ʼ��
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
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 			//GPIOA9��GPIOA10
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOA,&GPIO_InitStructure); 												//��ʼ��PA9��PA10	

		USART_InitStructure.USART_BaudRate = baud;										//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
		USART_Init(USART1, &USART_InitStructure); 																				//��ʼ������1	
			
		USART_Cmd(USART1, ENABLE);  																	//ʹ�ܴ���1
		
		USART_ClearFlag(USART1, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//����жϱ�־λ
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);								//��������жϣ�USART_IT_TC��USART_IT_TXE��USART_IT_RXNE��

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;							//����1�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);																//����ָ���Ĳ�����ʼ��VIC�Ĵ���			
	}
	
	if(USARTx == USART2)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		
		
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; 				//GPIOA2��GPIOA3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOA,&GPIO_InitStructure); 												//��ʼ��PA2��PA3		
		
		USART_InitStructure.USART_BaudRate = baud;										//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
		USART_Init(USART2, &USART_InitStructure); 																				//��ʼ������2	

		USART_Cmd(USART2, ENABLE);  																	//ʹ�ܴ���2
		
		USART_ClearFlag(USART2, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//����жϱ�־λ
		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);								//��������жϣ�USART_IT_TC��USART_IT_TXE��USART_IT_RXNE��

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;							//����2�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);																//����ָ���Ĳ�����ʼ��VIC�Ĵ���			
	}	

	if(USARTx == USART3)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);		
		
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); 
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 			//GPIOB10��GPIOB11
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOB,&GPIO_InitStructure); 												//��ʼ��PB10��PB11		
		
		USART_InitStructure.USART_BaudRate = baud;										//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
		USART_Init(USART3, &USART_InitStructure); 																				//��ʼ������3	

		USART_Cmd(USART3, ENABLE);  																	//ʹ�ܴ���3
		
		USART_ClearFlag(USART3, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//����жϱ�־λ
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);								//��������жϣ�USART_IT_TC��USART_IT_TXE��USART_IT_RXNE��

		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;							//����3�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);																//����ָ���Ĳ�����ʼ��VIC�Ĵ���			
	}	
	
	if(USARTx == UART4)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);		
		
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); 
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 			//GPIOC10��GPIOC11
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOC,&GPIO_InitStructure); 												//��ʼ��PC10��PC11		
		
		USART_InitStructure.USART_BaudRate = baud;										//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
		USART_Init(UART4, &USART_InitStructure); 																					//��ʼ������4	

		USART_Cmd(UART4, ENABLE);  																		//ʹ�ܴ���4
		
		USART_ClearFlag(UART4, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);					//����жϱ�־λ
		USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);								//��������жϣ�USART_IT_TC��USART_IT_TXE��USART_IT_RXNE��

		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;							//����4�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);																//����ָ���Ĳ�����ʼ��VIC�Ĵ���			
	}	


	if(USARTx == UART5)	
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);		
		
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART4); 
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART4); 	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 										//GPIOC12
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOC,&GPIO_InitStructure); 												//��ʼ��PC12		
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 										//GPIOD2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOD,&GPIO_InitStructure); 												//��ʼ��PD2				
		
		USART_InitStructure.USART_BaudRate = baud;										//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
		USART_Init(UART5, &USART_InitStructure); 																					//��ʼ������5	

		USART_Cmd(UART5, ENABLE);  																		//ʹ�ܴ���5
		
		USART_ClearFlag(UART5, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);					//����жϱ�־λ
		USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);								//��������жϣ�USART_IT_TC��USART_IT_TXE��USART_IT_RXNE��

		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;							//����5�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);																//����ָ���Ĳ�����ʼ��VIC�Ĵ���			
	}

	if(USARTx == USART6)												
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	 
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6); 
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 				//GPIOC6��GPIOC7
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 								//���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 									//����
		GPIO_Init(GPIOC,&GPIO_InitStructure); 												//��ʼ��PC6��PC7	

		USART_InitStructure.USART_BaudRate = baud;										//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
		USART_Init(USART6, &USART_InitStructure); 																				//��ʼ������6	
			
		USART_Cmd(USART6, ENABLE);  																	//ʹ�ܴ���6
		
		USART_ClearFlag(USART6, USART_FLAG_TC | USART_FLAG_RXNE | USART_FLAG_TXE);				//����жϱ�־λ
		USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);								//��������жϣ�USART_IT_TC��USART_IT_TXE��USART_IT_RXNE��

		NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;							//����6�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//�����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);																//����ָ���Ĳ�����ʼ��VIC�Ĵ���			
	}	
}



/*--------------------------------------------
note:���ڷ���
--------------------------------------------*/
INT8U uart_send_data(USART_TypeDef* USARTx, const char* buf, INT32U len)
{
	INT32U cycle = 0;
	if(USARTx == USART1)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);			//�ȴ��������		
			USART_SendData(USART1, *(buf+cycle));		
		}
	}
	
	if(USARTx == USART2)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);			//�ȴ��������		
			USART_SendData(USART2, *(buf+cycle));		
		}
	}	
	
	if(USARTx == USART3)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);			//�ȴ��������		
			USART_SendData(USART3, *(buf+cycle));		
		}
	}
	
	if(USARTx == UART4)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);				//�ȴ��������		
			USART_SendData(UART4, *(buf+cycle));		
		}
	}	
	
	if(USARTx == UART5)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);				//�ȴ��������		
			USART_SendData(UART5, *(buf+cycle));		
		}
	}	

	if(USARTx == USART6)	
	{
		for(cycle=0; cycle<len; cycle++)
		{
			while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);			//�ȴ��������		
			USART_SendData(USART6, *(buf+cycle));		
		}
	}	
	return 0;
}







