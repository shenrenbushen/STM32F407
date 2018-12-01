#ifndef _S_CRITICAL_H_
#define _S_CRITICAL_H_

#include "srbs_common.h"

#define SRBS_ENTER_CRITICAL							i_enter_critical()
#define SRBS_EXIT_CRITICAL							i_exit_critical()

INT8U enter_critical(void);
INT8U exit_critical(void);
INT8U inquire_critical(void);


#endif




























