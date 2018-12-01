#include "s_soft_timer.h"

#define TIMER_SOFT_NUM				5							

soft_timer_t timer_soft[TIMER_SOFT_NUM];
INT8U timer_soft_alloc = 0;

/*--------------------------------------------
note:�����ʱ����ʼ������
--------------------------------------------*/
void soft_timer_init(void)
{
	INT8U cycle = 0;																		
	for(cycle=0; cycle<TIMER_SOFT_NUM; cycle++)
	{
		timer_soft[cycle].flag = FALSE;
		timer_soft[cycle].cnt = 0;
		timer_soft[cycle].enable = FALSE;
		timer_soft[cycle].interval = 0;
		timer_soft[cycle].f_callback = NULL;
		timer_soft[cycle].f_callback_int = NULL;
	}
	//��Ҫ���Ӳ����ʱ����ʼ������
	
}

/*--------------------------------------------
note:��䣺Ӳ����ʱ���жϺ���
--------------------------------------------*/

/*--------------------------------------------
note:��ʱ�����жϼ�����0
--------------------------------------------*/
void soft_timer_reset_cnt(soft_timer_t *timer)
{
	timer->cnt = 0;
}

/*--------------------------------------------
note:������ʱ������ʱ��
--------------------------------------------*/
void soft_timer_set_interval(soft_timer_t *timer, TMR_CNT_INT interval)
{
	timer->interval = interval;
}

/*--------------------------------------------
note:ʹ����ʱ��
--------------------------------------------*/
void soft_timer_enable(soft_timer_t *timer, INT8U enable)
{
	timer->enable = enable;
}


/*--------------------------------------------
note:��ʱ��Ӳ���жϺ�������TIMER ISR���ã�
--------------------------------------------*/
void soft_timer_isr(void)
{
	INT8U cycle = 0;
	for(cycle=0; cycle<TIMER_SOFT_NUM; cycle++)
	{
		if(timer_soft[cycle].enable == TRUE)
		{
			if(0 != timer_soft[cycle].interval)
			{
				timer_soft[cycle].cnt++;
				if(timer_soft[cycle].cnt >= timer_soft[cycle].interval)
				{
					timer_soft[cycle].cnt = 0;
					if(timer_soft[cycle].f_callback != NULL && timer_soft[cycle].f_callback_int == NULL)
					{
						timer_soft[cycle].flag = TRUE;							
					}
					if(timer_soft[cycle].f_callback == NULL && timer_soft[cycle].f_callback_int != NULL)
					{
						timer_soft[cycle].f_callback_int(timer_soft[cycle].msg);
					}
				}				
			}
		}
	}	
}



/*--------------------------------------------
note:���������ʱ������
--------------------------------------------*/
soft_timer_t *soft_timer_creat(TMR_CNT_INT interval, INT8U enable, FUNC_TIMER f_callback, FUNC_TIMER f_callback_int, void *msg)
{
	if(timer_soft_alloc >= TIMER_SOFT_NUM)
	{
		return NULL;
	}
	timer_soft[timer_soft_alloc].interval = interval;
	timer_soft[timer_soft_alloc].enable = enable;
	timer_soft[timer_soft_alloc].f_callback = f_callback;
	timer_soft[timer_soft_alloc].f_callback_int = f_callback_int;
	timer_soft[timer_soft_alloc].msg = msg;
	
	timer_soft_alloc++;
	return &timer_soft[timer_soft_alloc-1];
}


/*--------------------------------------------
note:��ʱ�����жϴ�����
--------------------------------------------*/
void soft_timer_exc(void)
{
	INT8U cycle = 0;
	for(cycle=0; cycle<TIMER_SOFT_NUM; cycle++)
	{
		if(timer_soft[cycle].flag == TRUE)
		{
			timer_soft[cycle].flag = FALSE;
			if(timer_soft[cycle].f_callback != NULL)
			{
				timer_soft[cycle].f_callback(timer_soft[cycle].msg);
			}
		}
	}
}







