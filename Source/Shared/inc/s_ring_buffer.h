#ifndef _S_RING_BUFFER_H_
#define _S_RING_BUFFER_H_

#include "srbs_common.h"

typedef struct RING_BUFFER
{
	INT8U *buf;
	INT16U now;
	INT16U end;	
	INT16U size;
}ring_buffer_t;


ring_buffer_t *ring_buffer_creat(INT16U size);

void ring_buffer_destroy(ring_buffer_t *ring_buffer);

void ring_buffer_write_byte(ring_buffer_t *ring_buffer, INT8U dat);

INT8U ring_buffer_read_byte(ring_buffer_t *ring_buffer, INT8U *val);

INT16U ring_buffer_read_only(ring_buffer_t *ring_buffer, INT8U *buf, INT16U start, INT16U len);

INT16U ring_buffer_delet(ring_buffer_t *ring_buffer, INT16U len);

void ring_buffer_reset(ring_buffer_t *ring_buffer);

INT16U ring_buffer_get_length(ring_buffer_t *ring_buffer);



#endif





