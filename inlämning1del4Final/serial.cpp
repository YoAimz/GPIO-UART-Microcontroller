//Author: Yasin Rigi
//inlämningsuppgift 1 - GPIO . UART

#include "serial.h"


void uart_init() {
    
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8); //BAUD rate high
    UBRR0L = (uint8_t)(BAUD_PRESCALLER); //BAUD rate high
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // Enable TX, RX and RX interrupt
    UCSR0C = (3 << UCSZ00); //8 data bits, 1 stop bit
}

//uart_putchar function to send a single char over uart
void uart_putchar(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

//function to send a null-terminated string over UART
void uart_putstr(const char *str) {
    while (*str) {
        uart_putchar(*str);
        str++;
    }
    uart_putchar('\n');
}
//function to recive a single charachter from UART
unsigned char uart_getchar() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

//checks if data is being read from UART
bool uart_available() {
    return UCSR0A & (1 << RXC0);
}

unsigned char uart_readchar() {
    // Wait for data to be received
    //while (!(UCSR0A & (1 << RXC0)));
    // Get and return received data from buffer
    return UDR0;
}

