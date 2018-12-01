#ifndef _S_SOFT_TIMER_H_
#define _S_SOFT_TIMER_H_

#include "srbs_common.h"


typedef void (*FUNC_TIMER)(void *msg);										//定时器软中断函数	
typedef INT32U							TMR_CNT_INT;
typedef struct SOTF_TIMER																	//定时器结构体
{
	TMR_CNT_INT cnt;			
	INT8U flag;
	INT8U	enable;
	TMR_CNT_INT interval;
	FUNC_TIMER f_callback;
	FUNC_TIMER f_callback_int;
	void *msg;
}soft_timer_t;


void soft_timer_init(void);
void soft_timer_reset_cnt(soft_timer_t *timer);																
void soft_timer_set_interval(soft_timer_t *timer, TMR_CNT_INT interval);
void soft_timer_enable(soft_timer_t *timer, INT8U enable);
soft_timer_t *soft_timer_creat(TMR_CNT_INT interval, INT8U enable, FUNC_TIMER f_callback, FUNC_TIMER f_callback_int, void *msg);

void soft_timer_isr(void);
void soft_timer_exc(void);

#endif




