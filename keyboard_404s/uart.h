#ifndef __UART_H__
#define __UART_H__

#include "config.h"

#define UART_BUFFER_SIZE  8

#define OS_EVENT_UART_RECV_0 0x10
#define UART_START_CHECK 0x11
#define UART_END_CHECK 0X12

void os_uart_setup();
void os_uart_push( BYTE c );
void os_uart_flush();

void sendData(BYTE value);
void process_serial_data(BYTE S_data);
#endif