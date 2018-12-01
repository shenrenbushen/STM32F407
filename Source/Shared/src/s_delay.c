#include "s_delay.h"

/************************************************************************/
/******************************�ο�����ԭ��******************************/
/***********************************************************************/

#define TICK_PER_US											168								//1us����168��tick
   
/*--------------------------------------------
note:Systick��ʼ������
--------------------------------------------*/
void systick_init(u32 nus)
{ 
	SysTick_Config(TICK_PER_US*nus);												//����systickʱ�ӣ�������n usһ���ж�
}

/*--------------------------------------------
note:��ʱus����
--------------------------------------------*/    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told, tnow, tcnt = 0;
	u32 reload = SysTick->LOAD;						//SysTick->LOAD�ǵ��������Ƶ�0ʱ����װ�ص�ֵ	    	 
	ticks = nus * TICK_PER_US; 						//��Ҫ��ʱ�Ľ����� 
	told = SysTick->VAL;        					//SysTick->VAL�ǵ�ǰ��������ֵ
	while(1)
	{
		tnow = SysTick->VAL;	
		if(tnow != told)
		{	    
			if(tnow < told)
			{
				tcnt += told - tnow;
			}	
			else
			{
				tcnt += reload - tnow + told;	
			}    
			told = tnow;
			
			if(tcnt>=ticks) break;			
		}  
	}										    
} 

/*--------------------------------------------
note:��ʱms����
--------------------------------------------*/   
void delay_ms(u32 nms)
{
	u32 i;
	for(i=0; i<nms; i++) 
	{
		delay_us(1000);
	}
}















