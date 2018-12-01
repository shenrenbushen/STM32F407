#include "s_iwdg.h" 

//���Ź�ʹ�õ���LSIʱ�ӣ���Լ��32k��Ƶ�ʣ�ʱ�Ӳ���׼��prer�Ƿ�Ƶϵ����������7�ַ�Ƶ��ʽ��rlr��װ�ؼ�������ֵ��
//����LSI�ǳ���׼������������Ҫ�ڼ���ι��ʱ���1/4֮ǰȥι��
//@arg IWDG_Prescaler_4: IWDG prescaler set to 4
//@arg IWDG_Prescaler_8: IWDG prescaler set to 8
//@arg IWDG_Prescaler_16: IWDG prescaler set to 16
//@arg IWDG_Prescaler_32: IWDG prescaler set to 32
//@arg IWDG_Prescaler_64: IWDG prescaler set to 64
//@arg IWDG_Prescaler_128: IWDG prescaler set to 128
//@arg IWDG_Prescaler_256: IWDG prescaler set to 256


/*--------------------------------------------
note:�������Ź���ʼ������
--------------------------------------------*/
void iwdg_init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 		//ʹ�ܶ�IWDG->PR IWDG->RLR��д
	
	IWDG_SetPrescaler(prer); 													//����IWDG��Ƶϵ��

	IWDG_SetReload(rlr);   														//����IWDGװ��ֵ

	IWDG_ReloadCounter(); 														//װ�ؼ�����
	
	IWDG_Enable();       															//ʹ�ܿ��Ź�
}

/*--------------------------------------------
note:ι������
--------------------------------------------*/
void iwdg_feed(void)
{
	IWDG_ReloadCounter();															//װ�ؼ�����
}
















