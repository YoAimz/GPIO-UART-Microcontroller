//Author: Yasin Rigi
//inlämningsuppgift 1 - GPIO . UART

#ifndef SERIAL_H_
#define SERIAL_H_

#include <avr/io.h>
#include <stdbool.h>
#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void uart_init();
void uart_putchar(unsigned char data);
void uart_putstr(const char *str);
unsigned char uart_getchar();
bool uart_available();
unsigned char uart_readchar();

#endif /* SERIAL_H_ */
