#ifndef _S_USART_H_
#define _S_USART_H_

#include "srbs_common.h"

/*---------------------------*/
/* USART1:PA9(TX)、 PA10(RX) */
/* USART2:PA2(TX)、 PA3(RX)	 */
/* USART3:PB10(TX)、PB11(RX) */
/* UART4 :PC10(TX)、PC11(RX) */
/* UART5 :PC12(TX)、PD2(RX)	 */
/* USART6:PC6(TX)、 PD7(RX)	 */
/*---------------------------*/

void uart_init(USART_TypeDef* USARTx, INT32U baud);
INT8U uart_send_data(USART_TypeDef* USARTx, const char* buf, INT32U len);


#endif


