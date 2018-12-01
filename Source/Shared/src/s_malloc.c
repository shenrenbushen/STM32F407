#include "s_malloc.h"

//�ڴ�����趨
#define MEM_BLOCK_SIZE			8  	  							//�ڴ���СΪ8�ֽ�
#define MEM_MAX_SIZE			512  							//�������ڴ�512BYTE
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//�ڴ�����




void mem_init(void);
INT8U mem_used_rate(void);					//���ڴ�ʹ����(��/�ڲ�����) 

//�ڴ��(8�ֽڶ���)
__align(8) INT8U mem_pool[MEM_MAX_SIZE];				//SRAM�ڴ��
//�ڴ�����
INT16U mem_map[MEM_ALLOC_TABLE_SIZE];					//SRAM�ڴ��MAP


//�ڴ���������
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

//�ڴ�����ʼ��  
void mem_init(void)  
{  
    my_memset(mallco_dev.mem_map, 0, MEM_ALLOC_TABLE_SIZE * 2);					//�ڴ�״̬����������  
	my_memset(mallco_dev.mem_pool, 0, MEM_MAX_SIZE);							//�ڴ��������������  
	mallco_dev.mem_rdy = 1;														//�ڴ�����ʼ��OK  
}

INT32U used = 0;
//��ȡ�ڴ�ʹ����
//����ֵ:ʹ����(0~100)
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

//�ڴ����(�ڲ�����)
//memx:�����ڴ��
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ 
INT32U mem_malloc(INT32U size)  
{  
    signed long offset=0;  
    INT16U nmemb;				//��Ҫ���ڴ����  
	INT16U cmemb=0;				//�������ڴ����
    INT32U i;  
    if(!mallco_dev.mem_rdy) mallco_dev.init();	//δ��ʼ��,��ִ�г�ʼ�� 
    if(size == 0) return 0XFFFFFFFF;				//����Ҫ����
    nmemb = size/MEM_BLOCK_SIZE;  					//��ȡ��Ҫ����������ڴ����
    if(size % MEM_BLOCK_SIZE) nmemb++;  
    for(offset = MEM_ALLOC_TABLE_SIZE-1; offset>=0; offset--)	//���������ڴ������  
    {     
		if(!mallco_dev.mem_map[offset]) cmemb++;	//�������ڴ��������
		else cmemb = 0;							//�����ڴ������
		if(cmemb==nmemb)						//�ҵ�������nmemb�����ڴ��
		{
            for(i=0;i<nmemb;i++)  				//��ע�ڴ��ǿ� 
            {  
                mallco_dev.mem_map[offset+i]=nmemb;  
            }  
            return (offset*MEM_BLOCK_SIZE);			//����ƫ�Ƶ�ַ  
		}
    }  
    return 0XFFFFFFFF;//δ�ҵ����Ϸ����������ڴ��  
}


//�ͷ��ڴ�(�ڲ�����) 
//offset:�ڴ��ַƫ��
//����ֵ:0,�ͷųɹ�;1,�ͷ�ʧ��;  
INT8U mem_free(INT32U offset)  
{  
    int i;  
    if(!mallco_dev.mem_rdy)//δ��ʼ��,��ִ�г�ʼ��
	{
		mallco_dev.init();    
        return 1;//δ��ʼ��  
    }  
    if(offset < MEM_MAX_SIZE)//ƫ�����ڴ����. 
    {  
        int index = offset/MEM_BLOCK_SIZE;		//ƫ�������ڴ�����  
        int nmemb = mallco_dev.mem_map[index];	//�ڴ������
        for(i=0; i<nmemb; i++)  				//�ڴ������
        {  
            mallco_dev.mem_map[index+i] = 0;  
        }
        return 0;  
    }else return 2;//ƫ�Ƴ�����.  
} 


//�ͷ��ڴ�(�ⲿ����) 
//ptr:�ڴ��׵�ַ 
void my_free(void *ptr)  
{  
	INT32U offset;  
    if(ptr == NULL)return;//��ַΪ0.  
 	offset = (INT32U)ptr - (INT32U)mallco_dev.mem_pool;  
    mem_free(offset);	//�ͷ��ڴ�     
}  

//�����ڴ�(�ⲿ����)
//size:�ڴ��С(�ֽ�)
//����ֵ:���䵽���ڴ��׵�ַ.
void *my_malloc(INT32U size)  
{  
    INT32U offset;  									      
	offset = mem_malloc(size);  	   				   
    if(offset==0XFFFFFFFF) return NULL;  
    else return (void*)((INT32U)mallco_dev.mem_pool + offset);  
} 

//���·����ڴ�(�ⲿ����)
//*ptr:���ڴ��׵�ַ
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:�·��䵽���ڴ��׵�ַ.
void *my_realloc(void *ptr,INT32U size)  
{  
    INT32U offset;  
    offset = mem_malloc(size);  
    if(offset==0XFFFFFFFF) return NULL;     
    else  
    {  									   
	    my_memcpy((void*)((INT32U)mallco_dev.mem_pool+offset),ptr,size);	//�������ڴ����ݵ����ڴ�   
        my_free(ptr);  											  	//�ͷž��ڴ�
        return (void*)((INT32U)mallco_dev.mem_pool+offset);  			//�������ڴ��׵�ַ
    }  
}


