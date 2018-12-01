#ifndef _S_MALLOC_H_
#define _S_MALLOC_H_

#include "srbs_common.h"

typedef struct 
{
	void (*init)(void);						//初始化
	INT8U (*used_rate)(void);		  		//内存使用率
	INT8U *mem_pool;						//内存池 
	INT16U *mem_map; 						//内存管理状态表
	INT8U mem_rdy; 							//内存管理是否就绪
}mallco_dev_t;

extern mallco_dev_t mallco_dev;

void my_free(void *ptr);
void *my_malloc(INT32U size);
void *my_realloc(void *ptr,INT32U size);

#endif


