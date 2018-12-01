#ifndef _MALLOC_H_
#define _MALLOC_H_

/* ----------------------- Includes --------------------------------*/
#include "srbs_common.h"

typedef struct 
{
	void (*init)(void);						
	INT8U (*used_rate)(void);		  		
	INT8U *mem_pool;						
	INT16U *mem_map; 						
	INT8U mem_rdy; 							
}mallco_dev_t;

extern mallco_dev_t mallco_dev;

void my_free(void *ptr);
void *my_malloc(INT32U size);
void *my_realloc(void *ptr,INT32U size);

#endif


