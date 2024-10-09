# Microcontroller Programming

This repository contains a microcontroller programming project using Arduino/Freenove hardware, written in C/C++ using VSCode. The project avoids using Arduino's built-in software functions and focuses on direct manipulation of hardware registers.

## Part 1: Controlling an LED

### Overview
This part involves using GPIO pins to control an LED and detect button presses. It demonstrates basic GPIO manipulation without using Arduino functions.

### Implementation
- **Pin Configuration**: 
  - Pin 8 is configured as an output to control the LED.
  - Pin 9 is configured as an input to detect the button state.
- **Direct Register Manipulation**:
  - The GPIO pins are set up using the hardware registers for `DDRB` (Data Direction Register B). The output is controlled via `PORTB`, and the input is read from `PINB`.
- **Button Press Handling**:
  - The LED toggles between on and off states with each button press.
  - No debouncing or interrupts are used, making this a basic implementation.

### Explanation
This part illustrates how to set up and control microcontroller GPIO pins at a low level, bypassing Arduino’s abstractions for a deeper understanding of hardware operations.

## Part 2: UART Initialization and Sending Data

### Overview
This part focuses on setting up the UART (Universal Asynchronous Receiver-Transmitter) for communication and sending data using custom functions.

### Implementation
- **UART Initialization (`uart_init`)**:
  - Configures `USART0` for transmission (TX) using 9600 baud and the 8N1 format (8 data bits, no parity, 1 stop bit).
- **Sending a Character (`uart_putchar`)**:
  - This function sends a single character over the serial connection using `USART0`.
- **Sending a String (`uart_putstr`)**:
  - Uses `uart_putchar()` to send an entire string and appends a newline character (`\n`) at the end for formatting.

### Explanation
This part demonstrates the basics of serial communication by setting up UART manually and writing functions for transmitting data. It provides hands-on experience with configuring serial communication hardware directly.

## Part 3: UART Reception and Echo Function

### Overview
In this part, the project extends UART functionality to receive characters and respond in real-time.

### Implementation
- **UART Reception (`uart_getchar`)**:
  - Configures the system to receive a single character from the serial input.
- **Echo Function (`uart_echo`)**:
  - Waits for an incoming character using `uart_getchar()` and immediately sends the same character back using `uart_putchar()`.
  - This function can either block (wait for input) or return without action if no character is read.

### Explanation
This part demonstrates how to receive data over UART and respond immediately. It simulates a basic echo server, providing an opportunity to work with serial input/output processing.

## Part 4: UART Command Handling

### Overview
The final part adds complexity by reading complete commands from the serial input and parsing them to control the LED based on the value provided.

### Implementation
- **Receiving Strings (`uart_rec_str`)**:
  - Reads a full line of input until a newline character (`\n`) is detected. This can be done using interrupts or a loop that ensures all characters are read in time.
- **Command Parsing**:
  - Uses `sscanf()` to parse the command and extract integer values, e.g., parsing a command like `"ledpower %d"` to retrieve an integer representing the power level.
  - The command `"ledpower <value>"` accepts values from 0 to 255. 
  - If the value is above 127, the LED turns on; if it is 127 or below, the LED turns off.

### Explanation
This part introduces command parsing and the use of serial communication to control hardware dynamically based on user input. It demonstrates how to implement more advanced logic and interaction through serial communication.

## Conclusion

This project provides a comprehensive understanding of low-level microcontroller programming, focusing on GPIO and UART functionalities without relying on Arduino's built-in abstractions. The code is modular, with each part organized into separate files like `main.c`, `serial.c`, and `serial.h` for clarity and reusability.
