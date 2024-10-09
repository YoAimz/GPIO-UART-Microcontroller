//Author: Yasin Rigi
//inlämningsuppgift 1 - GPIO . UART
// part 1 and 2 and 3

#include <avr/io.h>
#include "serial.h"

#define LED_PIN PB0
#define BUTTON_PORT PORTB
#define BUTTON_PIN PB1
#define LED_DDR DDRB

void gpioSETUP() {
    //data direction register to set pb0 (pin 8) as a output
    LED_DDR |= (1 << LED_PIN);
    // << = shift operator
    // 1 shift to the left PINB, meaning it will turn the PB0 as output

    //THE BUTTON PIN AS INPUT (PB1)t
    LED_DDR &= ~(1 << BUTTON_PIN);

    //pull-up resistor on BUTTON_PIN
    BUTTON_PORT |= (1 << BUTTON_PIN);
}

void loop() {
    
        
        if (!bit_is_clear(PINB, BUTTON_PIN)) {
            BUTTON_PORT |= (1 << LED_PIN); //turn on LED
        } else {
            BUTTON_PORT &= ~(1 << LED_PIN); //turn off LED
        }

        //check if character received
        if (uart_available()) {
            char receivedChar = uart_getchar(); //read character from UART
            uart_putchar(receivedChar);         //echo back the received character
        }

}

int main() {
    //initialize GPIO and UART
    gpioSETUP();
    uart_init();

    //testing TX
    uart_putstr("TX working!\n");
    
    while (1) {
        loop(); 
    }

    return 0;
}
