#ifndef _S_MALLOC_H_
#define _S_MALLOC_H_

#include "srbs_common.h"

typedef struct 
{
	void (*init)(void);						//��ʼ��
	INT8U (*used_rate)(void);		  		//�ڴ�ʹ����
	INT8U *mem_pool;						//�ڴ�� 
	INT16U *mem_map; 						//�ڴ����״̬��
	INT8U mem_rdy; 							//�ڴ�����Ƿ����
}mallco_dev_t;

extern mallco_dev_t mallco_dev;

void my_free(void *ptr);
void *my_malloc(INT32U size);
void *my_realloc(void *ptr,INT32U size);

#endif


