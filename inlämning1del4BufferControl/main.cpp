//Author: Yasin Rigi
//inlämningsuppgift 1 - GPIO . UART

// !READ!
// command example "ledpower127" 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "serial.h"

#define RX_BUF_SIZE 64
#define LED_PIN PB0
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_POWER_CMD "ledpower"
#define LED_OFF_CMD 127
#define LED_ON_CMD 1
#define LED_MAX_VALUE 255
#define IS_LED_POWER_VALID(res) ((res) == 1)
#define IS_LED_VALUE_VALID(value) ((value) >= 0)


//volatile char receivedString[RX_BUF_SIZE]; //buffer to store rx characters
volatile char *receivedString = nullptr;
volatile uint8_t receivedStringIndex = 0; //index variable for the received string buffer
volatile bool stringComplete = false; //flag for when complete string has been recevied


void gpioSETUP() {
    LED_DDR |= (1 << LED_PIN);  //set LED_PIN as output
}


void setLedOn(bool on) {
    if (on) {
        LED_PORT |= (1 << LED_PIN); // Turn on LED
    } else {
        LED_PORT &= ~(1 << LED_PIN); // Turn off LED
    }
}

//function to receive string
void uart_rec_str() {
    if (receivedString == nullptr) {

        receivedString = new char[RX_BUF_SIZE];
    }
    while (uart_available()) {
        char receivedChar = uart_readchar();
        if (receivedChar == '\n') {
            receivedString[receivedStringIndex] = '\0';
            receivedStringIndex = 0;
            stringComplete = true;
            return;
        }
        if (receivedStringIndex < RX_BUF_SIZE - 1) {
            receivedString[receivedStringIndex++] = receivedChar;
        } else {
            uart_putstr("BUFFER OVERFLOW!\n");
            delete[] receivedString;
            receivedString = nullptr;
            receivedStringIndex = 0;
        }
    }
}

//parse recived command
void parseCommand() {
    int value = -1;
    int res = sscanf((const char*)receivedString, LED_POWER_CMD " %d", &value);
    if (IS_LED_POWER_VALID(res) && IS_LED_VALUE_VALID(value) && value <= LED_MAX_VALUE) {
        bool turnOnLED = (value > LED_OFF_CMD);
        setLedOn(turnOnLED);
    }
}


void loop() {
    if (stringComplete) {
        parseCommand();
        stringComplete = false;
    }
}


int main() {
    gpioSETUP();
    uart_init();
    uart_putstr("TX working!\n");
    sei(); 

    while (1) {
        loop(); 
    }

    delete[] receivedString;
    return 0;
}


// UART receive interrupt service routine
ISR(USART_RX_vect) {
    uart_rec_str();
}

