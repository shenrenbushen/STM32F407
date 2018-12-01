#include "s_malloc.h"

//内存参数设定
#define MEM_BLOCK_SIZE			8  	  							//内存块大小为8字节
#define MEM_MAX_SIZE			512  							//最大管理内存512BYTE
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//内存表个数




void mem_init(void);
INT8U mem_used_rate(void);					//得内存使用率(外/内部调用) 

//内存池(8字节对齐)
__align(8) INT8U mem_pool[MEM_MAX_SIZE];				//SRAM内存池
//内存管理表
INT16U mem_map[MEM_ALLOC_TABLE_SIZE];					//SRAM内存池MAP


//内存管理控制器
mallco_dev_t mallco_dev = 
{
	mem_init,
	mem_used_rate,
	mem_pool,
	mem_map,
	0,
};


void my_memcpy(void *des,void *src,INT32U n)  
{  
    INT8U *xdes=des;
	INT8U *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  

void my_memset(void *s,INT8U c,INT32U count)  
{  
    INT8U *xs = s;  
    while(count--)*xs++=c;  
}

//内存管理初始化  
void mem_init(void)  
{  
    my_memset(mallco_dev.mem_map, 0, MEM_ALLOC_TABLE_SIZE * 2);					//内存状态表数据清零  
	my_memset(mallco_dev.mem_pool, 0, MEM_MAX_SIZE);							//内存池所有数据清零  
	mallco_dev.mem_rdy = 1;														//内存管理初始化OK  
}

INT32U used = 0;
//获取内存使用率
//返回值:使用率(0~100)
INT8U mem_used_rate(void)  
{  
    used = 0;  
    INT32U i;  
    for(i=0; i<MEM_ALLOC_TABLE_SIZE; i++)  
    {  
        if(mallco_dev.mem_map[i])used++; 
    } 
    return (used * 100)/(MEM_ALLOC_TABLE_SIZE);  
}  

//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址 
INT32U mem_malloc(INT32U size)  
{  
    signed long offset=0;  
    INT16U nmemb;				//需要的内存块数  
	INT16U cmemb=0;				//连续空内存块数
    INT32U i;  
    if(!mallco_dev.mem_rdy) mallco_dev.init();	//未初始化,先执行初始化 
    if(size == 0) return 0XFFFFFFFF;				//不需要分配
    nmemb = size/MEM_BLOCK_SIZE;  					//获取需要分配的连续内存块数
    if(size % MEM_BLOCK_SIZE) nmemb++;  
    for(offset = MEM_ALLOC_TABLE_SIZE-1; offset>=0; offset--)	//搜索整个内存控制区  
    {     
		if(!mallco_dev.mem_map[offset]) cmemb++;	//连续空内存块数增加
		else cmemb = 0;							//连续内存块清零
		if(cmemb==nmemb)						//找到了连续nmemb个空内存块
		{
            for(i=0;i<nmemb;i++)  				//标注内存块非空 
            {  
                mallco_dev.mem_map[offset+i]=nmemb;  
            }  
            return (offset*MEM_BLOCK_SIZE);			//返回偏移地址  
		}
    }  
    return 0XFFFFFFFF;//未找到符合分配条件的内存块  
}


//释放内存(内部调用) 
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;  
INT8U mem_free(INT32U offset)  
{  
    int i;  
    if(!mallco_dev.mem_rdy)//未初始化,先执行初始化
	{
		mallco_dev.init();    
        return 1;//未初始化  
    }  
    if(offset < MEM_MAX_SIZE)//偏移在内存池内. 
    {  
        int index = offset/MEM_BLOCK_SIZE;		//偏移所在内存块号码  
        int nmemb = mallco_dev.mem_map[index];	//内存块数量
        for(i=0; i<nmemb; i++)  				//内存块清零
        {  
            mallco_dev.mem_map[index+i] = 0;  
        }
        return 0;  
    }else return 2;//偏移超区了.  
} 


//释放内存(外部调用) 
//ptr:内存首地址 
void my_free(void *ptr)  
{  
	INT32U offset;  
    if(ptr == NULL)return;//地址为0.  
 	offset = (INT32U)ptr - (INT32U)mallco_dev.mem_pool;  
    mem_free(offset);	//释放内存     
}  

//分配内存(外部调用)
//size:内存大小(字节)
//返回值:分配到的内存首地址.
void *my_malloc(INT32U size)  
{  
    INT32U offset;  									      
	offset = mem_malloc(size);  	   				   
    if(offset==0XFFFFFFFF) return NULL;  
    else return (void*)((INT32U)mallco_dev.mem_pool + offset);  
} 

//重新分配内存(外部调用)
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
void *my_realloc(void *ptr,INT32U size)  
{  
    INT32U offset;  
    offset = mem_malloc(size);  
    if(offset==0XFFFFFFFF) return NULL;     
    else  
    {  									   
	    my_memcpy((void*)((INT32U)mallco_dev.mem_pool+offset),ptr,size);	//拷贝旧内存内容到新内存   
        my_free(ptr);  											  	//释放旧内存
        return (void*)((INT32U)mallco_dev.mem_pool+offset);  			//返回新内存首地址
    }  
}


