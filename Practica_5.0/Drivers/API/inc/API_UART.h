/*
 * API_UART.h
 *
 *  Created on: 24 sep. 2022
 *      Author: Santiago
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Exported typedefine ------------------------------------------------------------*/
typedef bool bool_t;

//Define UART functions
bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);




#endif /* API_INC_API_UART_H_ */
