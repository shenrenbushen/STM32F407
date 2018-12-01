#include "s_timer.h" 

/*--------------------------------------------
note:Timer6初始化函数
--------------------------------------------*/
void timer6_init(INT16U arr,INT16U psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM6, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = arr;		
	TIM_TimeBaseStructure.TIM_Prescaler= psc;									//Tout= ((arr+1)*(psc+1))/Tclk
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6, ENABLE);	
}

/*--------------------------------------------
note:Timer7初始化函数
--------------------------------------------*/
void timer7_init(INT16U arr,INT16U psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM7, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = arr;		
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM7, ENABLE);																		
}










