#include "s_ring_buffer.h"

//正常情况下now指向的空间必须为空，end指向的空间只能在没有数据的时候为空

/*--------------------------------------------
note:环形缓冲自增
--------------------------------------------*/
static INT16U ring_buffer_self_add(INT16U index, INT16U max_size)
{
	return ((index+1)%max_size);
}

/*--------------------------------------------
note:环形缓冲相加
--------------------------------------------*/
static INT16U ring_buffer_add(INT16U a, INT16U b, INT16U max_size)
{
	return ((a+b)%max_size);
}

/*--------------------------------------------
note:环形缓冲清0
--------------------------------------------*/
void ring_buffer_reset(ring_buffer_t *ring_buffer)
{
	ring_buffer->now = 0;
	ring_buffer->end = ring_buffer->now;
	
	if(NULL == ring_buffer->buf) return;
	
	memset((void*)ring_buffer->buf, 0, ring_buffer->size);	
}

/*--------------------------------------------
note:创建环形缓冲(p为配置的buf)
--------------------------------------------*/
ring_buffer_t *ring_buffer_creat(INT16U size)
{
	ring_buffer_t *ring_buffer_p = NULL;
	ring_buffer_p = malloc(sizeof(ring_buffer_t) + size*sizeof(INT8U));
	
	if(NULL == ring_buffer_p) return NULL;
	
	ring_buffer_p->buf = (INT8U*)(ring_buffer_p + 1);
	ring_buffer_p->now = 0;
	ring_buffer_p->end = ring_buffer_p->now;
	ring_buffer_p->size = size;
	
	memset((void*)ring_buffer_p->buf, 0, ring_buffer_p->size);
	
	return ring_buffer_p;
}

/*--------------------------------------------
note:删除环形缓冲(p为配置的buf)
--------------------------------------------*/
void ring_buffer_destroy(ring_buffer_t *ring_buffer)
{
	free(ring_buffer);
}

/*--------------------------------------------
note:向环形缓冲写一个字节
--------------------------------------------*/
void ring_buffer_write_byte(ring_buffer_t *ring_buffer, INT8U dat)
{
	INT16U temp_in = 0;
	enter_critical();
	temp_in = ring_buffer_self_add(ring_buffer->now, ring_buffer->size);
	if(temp_in != ring_buffer->end)				
	{
		ring_buffer->buf[ring_buffer->now] = dat;
		ring_buffer->now = temp_in;
	}
	exit_critical();
}


/*--------------------------------------------
note:从环形缓冲读出一个字节（val是读出的数据，返回值表示成功或不成功）
--------------------------------------------*/
INT8U ring_buffer_read_byte(ring_buffer_t *ring_buffer, INT8U *val)
{
	enter_critical();
	if(ring_buffer->end != ring_buffer->now)
	{
		*val = ring_buffer->buf[ring_buffer->end];				//读出数据
		ring_buffer->end = ring_buffer_self_add(ring_buffer->end, ring_buffer->size);			//out环形自增
		exit_critical();
		return 0;
	}
	exit_critical();
	return 1;
}


/*--------------------------------------------
note:获取缓存换长度
--------------------------------------------*/
INT16U ring_buffer_get_length(ring_buffer_t *ring_buffer)
{
	INT16U len = 0;
	enter_critical();
	len = (ring_buffer->now + ring_buffer->size - ring_buffer->end) % ring_buffer->size;		//当in小于out这种做法就显得有必要了（跑完一圈归0）
	exit_critical();
	return len;
}


/*--------------------------------------------
note:从环形缓冲读若干字节，返回值表示实际读出的个数，此函数只读但是不删除
--------------------------------------------*/
INT16U ring_buffer_read_only(ring_buffer_t *ring_buffer, INT8U *buf, INT16U start, INT16U len)
{
	//buf 读出数据的缓存  start 读缓存环起始位置  len 读取长度
	INT16U read_len = ring_buffer_get_length(ring_buffer);
	INT16U start_index = 0;
	INT16U cycle = 0;
	
	if(start >= read_len) return 0;	
	
	if(read_len >= (start + len))			//满足缓存换长度的情况下
	{
		read_len = len;
	}
	else
	{
		read_len = read_len - start;		//从start开始到缓存环结束能读的最大的长度
	}
	enter_critical();
	start_index = ring_buffer_add(start, ring_buffer->end, ring_buffer->size);
	exit_critical();	
	for(cycle=0; cycle<read_len ;cycle++)
	{
		enter_critical();
		buf[cycle] = ring_buffer->buf[start_index];
		start_index = ring_buffer_self_add(start_index, ring_buffer->size);
		exit_critical();
	}
	return read_len;
}

/*--------------------------------------------
note:删除缓存环
--------------------------------------------*/
INT16U ring_buffer_delet(ring_buffer_t *ring_buffer, INT16U len)
{
	INT16U read_len = ring_buffer_get_length(ring_buffer);
	enter_critical();
	if(read_len <= len)					//实际长度小于要删除的长度，此时删除全部缓存
	{
		ring_buffer->end = ring_buffer->now;
		exit_critical();
		return read_len;
	}
	ring_buffer->end = ring_buffer_add(ring_buffer->end, len, ring_buffer->size);
	exit_critical();
	return len;
}












