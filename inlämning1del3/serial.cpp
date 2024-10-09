//Author: Yasin Rigi
//inlämningsuppgift 1 - 

#include <avr/io.h>
#include "serial.h"

//debuggimh
bool uart_available() {
    //check if data has been received
    return UCSR0A & (1 << RXC0);
}

void uart_init() {
    //setting baud rate
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);

    //enables transmitter and receiver
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    //setting frame format: 8 data bits, 1 stop bit
    UCSR0C = (3 << UCSZ00);
}

void uart_putchar(unsigned char data) {
    //wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    //put data into buffer, sends the data
    UDR0 = data;
}

void uart_putstr(const char *str) {
    while (*str) {
        uart_putchar(*str);
        str++;
    }
    uart_putchar('\n');
}

unsigned char uart_getchar() {
    //waiting for data to be received
    while (!(UCSR0A & (1 << RXC0)));

    //get and return received data from buffer
    return UDR0;
}
