#include "s_ring_buffer.h"

//���������nowָ��Ŀռ����Ϊ�գ�endָ��Ŀռ�ֻ����û�����ݵ�ʱ��Ϊ��

/*--------------------------------------------
note:���λ�������
--------------------------------------------*/
static INT16U ring_buffer_self_add(INT16U index, INT16U max_size)
{
	return ((index+1)%max_size);
}

/*--------------------------------------------
note:���λ������
--------------------------------------------*/
static INT16U ring_buffer_add(INT16U a, INT16U b, INT16U max_size)
{
	return ((a+b)%max_size);
}

/*--------------------------------------------
note:���λ�����0
--------------------------------------------*/
void ring_buffer_reset(ring_buffer_t *ring_buffer)
{
	ring_buffer->now = 0;
	ring_buffer->end = ring_buffer->now;
	
	if(NULL == ring_buffer->buf) return;
	
	memset((void*)ring_buffer->buf, 0, ring_buffer->size);	
}

/*--------------------------------------------
note:�������λ���(pΪ���õ�buf)
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
note:ɾ�����λ���(pΪ���õ�buf)
--------------------------------------------*/
void ring_buffer_destroy(ring_buffer_t *ring_buffer)
{
	free(ring_buffer);
}

/*--------------------------------------------
note:���λ���дһ���ֽ�
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
note:�ӻ��λ������һ���ֽڣ�val�Ƕ��������ݣ�����ֵ��ʾ�ɹ��򲻳ɹ���
--------------------------------------------*/
INT8U ring_buffer_read_byte(ring_buffer_t *ring_buffer, INT8U *val)
{
	enter_critical();
	if(ring_buffer->end != ring_buffer->now)
	{
		*val = ring_buffer->buf[ring_buffer->end];				//��������
		ring_buffer->end = ring_buffer_self_add(ring_buffer->end, ring_buffer->size);			//out��������
		exit_critical();
		return 0;
	}
	exit_critical();
	return 1;
}


/*--------------------------------------------
note:��ȡ���滻����
--------------------------------------------*/
INT16U ring_buffer_get_length(ring_buffer_t *ring_buffer)
{
	INT16U len = 0;
	enter_critical();
	len = (ring_buffer->now + ring_buffer->size - ring_buffer->end) % ring_buffer->size;		//��inС��out�����������Ե��б�Ҫ�ˣ�����һȦ��0��
	exit_critical();
	return len;
}


/*--------------------------------------------
note:�ӻ��λ���������ֽڣ�����ֵ��ʾʵ�ʶ����ĸ������˺���ֻ�����ǲ�ɾ��
--------------------------------------------*/
INT16U ring_buffer_read_only(ring_buffer_t *ring_buffer, INT8U *buf, INT16U start, INT16U len)
{
	//buf �������ݵĻ���  start �����滷��ʼλ��  len ��ȡ����
	INT16U read_len = ring_buffer_get_length(ring_buffer);
	INT16U start_index = 0;
	INT16U cycle = 0;
	
	if(start >= read_len) return 0;	
	
	if(read_len >= (start + len))			//���㻺�滻���ȵ������
	{
		read_len = len;
	}
	else
	{
		read_len = read_len - start;		//��start��ʼ�����滷�����ܶ������ĳ���
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
note:ɾ�����滷
--------------------------------------------*/
INT16U ring_buffer_delet(ring_buffer_t *ring_buffer, INT16U len)
{
	INT16U read_len = ring_buffer_get_length(ring_buffer);
	enter_critical();
	if(read_len <= len)					//ʵ�ʳ���С��Ҫɾ���ĳ��ȣ���ʱɾ��ȫ������
	{
		ring_buffer->end = ring_buffer->now;
		exit_critical();
		return read_len;
	}
	ring_buffer->end = ring_buffer_add(ring_buffer->end, len, ring_buffer->size);
	exit_critical();
	return len;
}












