#ifndef _SRBS_COMMON_H_
#define _SRBS_COMMON_H_

#ifndef	TRUE
	#define TRUE (1 == 1)
#endif

#ifndef	FALSE
	#define FALSE (1 == 0)
#endif

#ifndef	NULL
	#define NULL (void *)0					
#endif

typedef unsigned char 			INT8U;
typedef signed char					INT8S;
typedef unsigned short 			INT16U;
typedef signed short				INT16S;
typedef unsigned int 				INT32U;
typedef signed int					INT32S;
typedef unsigned long long 	INT64U;
typedef signed long long 		INT64S;

/* ----------------------- System includes --------------------------------*/
#include "stm32f4xx.h"

/* ----------------------- Standard includes --------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ----------------------- Shared includes --------------------------------*/	
#include "s_critical.h"
#include "s_delay.h"
#include "s_debug.h" 



#endif




