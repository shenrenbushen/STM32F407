#include "main.h"
#include "s_debug.h"  
#include "s_usart.h"  
#include "s_iwdg.h" 
#include "malloc.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	systick_init(10000);
	debug_init(115200);
	
	printf("\r\n******************* start *******************\r\n");
	
	mallco_dev.init();
	
	printf("used_rate = %d.\r\n", mallco_dev.used_rate());
	
	INT8U *p = my_malloc(200*sizeof(INT8U));
	
	if(NULL != p)
	{
		printf("p = 0x%p.\r\n", p);
		sprintf((char*)p, "HELLO");
		printf("%s.\r\n", p);		
	}	
	else
	{
		printf("malloc error.\r\n");
	}
	
	INT8U *p1 = my_malloc(311*sizeof(INT8U));
	
	if(NULL != p1)
	{
		printf("p = 0x%p.\r\n", p1);
		sprintf((char*)p1, "HELLO p1");
		printf("%s.\r\n", p1);		
	}	
	else
	{
		printf("malloc error p1.\r\n");
	}

	printf("used_rate = %d.\r\n", mallco_dev.used_rate());
	
	my_free(p);
	
	printf("used_rate = %d.\r\n", mallco_dev.used_rate());
	
	my_free(p1);
	
	printf("used_rate = %d.\r\n", mallco_dev.used_rate());
	
	while(1)
	{

	}
}



















