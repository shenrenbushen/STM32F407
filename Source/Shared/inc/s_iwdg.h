#ifndef _S_IWDG_H_
#define _S_IWDG_H_

#include "srbs_common.h"

void iwdg_init(u8 prer,u16 rlr);
void iwdg_feed(void);

#endif


