#include "malloc.h"

/* ----------------------- Define --------------------------------*/
#define MEM_BLOCK_SIZE			8  	  							
#define MEM_MAX_SIZE			512  							//memory pool size
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//num of memory table

/* ----------------------- Static Function --------------------------------*/
static void mem_init(void);
static INT8U mem_used_rate(void);		
static void my_memcpy(void *des,void *src, INT32U n);
static void my_memset(void *s,INT8U c, INT32U count);
static INT32U mem_malloc(INT32U size);
static INT8U mem_free(INT32U offset);

/* ----------------------- Variable --------------------------------*/
__align(8) INT8U mem_pool[MEM_MAX_SIZE] = {0};				
INT16U mem_map[MEM_ALLOC_TABLE_SIZE] = {0};		

mallco_dev_t mallco_dev = 
{
	mem_init,
	mem_used_rate,
	mem_pool,
	mem_map,
	0,
};

/*--------------------------------------------
note:free
--------------------------------------------*/
void my_free(void *ptr)  
{  
	INT32U offset;  
    if(ptr == NULL) return;  
 	offset = (INT32U)ptr - (INT32U)mallco_dev.mem_pool;  
    mem_free(offset);	    
}  

/*--------------------------------------------
note:memory alloc (return: NULL shows failure)
--------------------------------------------*/
void *my_malloc(INT32U size)  
{  
    INT32U offset;  									      
	offset = mem_malloc(size);  	   				   
    if(offset == 0XFFFFFFFF) return NULL;  
    else return (void*)((INT32U)mallco_dev.mem_pool + offset);  
} 

/*--------------------------------------------
note:memory re_alloc 
--------------------------------------------*/
void *my_realloc(void *ptr,INT32U size)  
{  
    INT32U offset;  
    offset = mem_malloc(size);  
    if(offset == 0XFFFFFFFF) return NULL;     
    else  
    {  									   
	    my_memcpy((void*)((INT32U)mallco_dev.mem_pool+offset),ptr,size);	 
        my_free(ptr);  											  	
        return (void*)((INT32U)mallco_dev.mem_pool+offset);  			
    }  
}

static void my_memcpy(void *des,void *src, INT32U n)  
{  
    INT8U *xdes=des;
	INT8U *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  

static void my_memset(void *s,INT8U c, INT32U count)  
{  
    INT8U *xs = s;  
    while(count--)*xs++=c;  
}
 
static void mem_init(void)  
{  
    my_memset(mallco_dev.mem_map, 0, MEM_ALLOC_TABLE_SIZE * 2);					
	my_memset(mallco_dev.mem_pool, 0, MEM_MAX_SIZE);							  
	mallco_dev.mem_rdy = 1;														 
}

static INT8U mem_used_rate(void)  
{  
    INT32U used = 0;
    INT32U i;  
    for(i=0; i<MEM_ALLOC_TABLE_SIZE; i++)  
    {  
        if(mallco_dev.mem_map[i])used++; 
    } 
    return (used * 100)/(MEM_ALLOC_TABLE_SIZE);  
}  

static INT32U mem_malloc(INT32U size)  
{  
    signed long offset=0;  
    INT16U nmemb;				 
	INT16U cmemb=0;				
    INT32U i;  
    if(!mallco_dev.mem_rdy) mallco_dev.init();	
    if(size == 0) return 0XFFFFFFFF;				
    nmemb = size/MEM_BLOCK_SIZE;  					
    if(size % MEM_BLOCK_SIZE) nmemb++;  
    for(offset = MEM_ALLOC_TABLE_SIZE-1; offset>=0; offset--)	  
    {     
		if(!mallco_dev.mem_map[offset]) cmemb++;	
		else cmemb = 0;							
		if(cmemb==nmemb)						
		{
            for(i=0;i<nmemb;i++)  				
            {  
                mallco_dev.mem_map[offset+i]=nmemb;  
            }  
            return (offset*MEM_BLOCK_SIZE);			 
		}
    }  
    return 0XFFFFFFFF;
}

static INT8U mem_free(INT32U offset)  
{  
    int i;  
    if(!mallco_dev.mem_rdy)
	{
		mallco_dev.init();    
        return 1; 
    }  
    if(offset < MEM_MAX_SIZE)
    {  
        int index = offset/MEM_BLOCK_SIZE;		  
        int nmemb = mallco_dev.mem_map[index];	
        for(i=0; i<nmemb; i++)  				
        {  
            mallco_dev.mem_map[index+i] = 0;  
        }
        return 0;  
    }else return 2;
} 



