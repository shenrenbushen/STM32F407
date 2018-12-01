#include "s_delay.h"

/************************************************************************/
/******************************参考正点原子******************************/
/***********************************************************************/

#define TICK_PER_US											168								//1us产生168个tick
   
/*--------------------------------------------
note:Systick初始化函数
--------------------------------------------*/
void systick_init(u32 nus)
{ 
	SysTick_Config(TICK_PER_US*nus);												//开启systick时钟，并设置n us一次中断
}

/*--------------------------------------------
note:延时us函数
--------------------------------------------*/    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told, tnow, tcnt = 0;
	u32 reload = SysTick->LOAD;						//SysTick->LOAD是当计数器计到0时，重装载的值	    	 
	ticks = nus * TICK_PER_US; 						//需要延时的节拍数 
	told = SysTick->VAL;        					//SysTick->VAL是当前计数器的值
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
note:延时ms函数
--------------------------------------------*/   
void delay_ms(u32 nms)
{
	u32 i;
	for(i=0; i<nms; i++) 
	{
		delay_us(1000);
	}
}















