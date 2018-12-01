#include "s_iwdg.h" 

//看门狗使用的是LSI时钟，大约在32k的频率，时钟不精准，prer是分频系数，有以下7种分频方式。rlr是装载计数器的值。
//由于LSI非常不准，所以我们需要在计算喂狗时间的1/4之前去喂狗
//@arg IWDG_Prescaler_4: IWDG prescaler set to 4
//@arg IWDG_Prescaler_8: IWDG prescaler set to 8
//@arg IWDG_Prescaler_16: IWDG prescaler set to 16
//@arg IWDG_Prescaler_32: IWDG prescaler set to 32
//@arg IWDG_Prescaler_64: IWDG prescaler set to 64
//@arg IWDG_Prescaler_128: IWDG prescaler set to 128
//@arg IWDG_Prescaler_256: IWDG prescaler set to 256


/*--------------------------------------------
note:独立看门狗初始化函数
--------------------------------------------*/
void iwdg_init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 		//使能对IWDG->PR IWDG->RLR的写
	
	IWDG_SetPrescaler(prer); 													//设置IWDG分频系数

	IWDG_SetReload(rlr);   														//设置IWDG装载值

	IWDG_ReloadCounter(); 														//装载计数器
	
	IWDG_Enable();       															//使能看门狗
}

/*--------------------------------------------
note:喂狗函数
--------------------------------------------*/
void iwdg_feed(void)
{
	IWDG_ReloadCounter();															//装载计数器
}
















