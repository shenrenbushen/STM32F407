#ifndef _S_DEBUG_H_
#define _S_DEBUG_H_

#include "srbs_common.h"

#define DEBUG_USE_WHICH_UART		USART1

void debug_init(u32 baudrate);
void debug_output(const char* buf,u32 len);


#endif

