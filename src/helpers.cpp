#include <avr/io.h>
#include "helpers.h"

void UART_init(uint16_t baud) {
  uint16_t baud_setting = F_CPU / 16 / baud - 1;
  UBRR0H = (baud_setting >> 8);
  UBRR0L = baud_setting;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_transmit(char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void UART_print(const char* str) {
  while (*str) {
    UART_transmit(*str++);
  }
}

void UART_println(const char* str) {
  UART_print(str);
  UART_print("\r\n");
}

void UART_print_int(uint32_t number) {
    if (number == 0) {
        UART_transmit('0');
        return;
    }

    char buffer[11]; // Enough for 10 digits + null terminator (uint32_t max is 4294967295 = 10 digits + null)
    uint8_t buffer_index = 0;

    while(number > 0) {
        char digit = (number % 10) + '0'; // Convert digit to character
        buffer[buffer_index] = digit; // Assign the character to the current buffer index
        buffer_index++; // Increment the buffer index
        number /= 10; // Remove the least significant digit from the number
    }

    while (buffer_index > 0) {
        UART_transmit(buffer[--buffer_index]);
    }
    UART_print("\r\n");
    UART_print("\r\n");
}

bool buttonPressed(const Button& button) {
    return (!button.currentState && button.lastState);
}

void updateButton(Button& button, volatile uint8_t& pinRegister, uint8_t pin) {
    button.lastState = button.currentState;

    button.currentState = pinRegister & (1 << pin);
}

void adjustInterval(Button& button, uint16_t& interval, bool increase) {
  auto changeInterval = [&]() {
    if(increase) {
      if(interval > 100) {
        interval -= 100;
        UART_println("Blink interval rate increased");
        UART_print_int(interval);
      }
    } else {
      if(interval < 60000) {
        interval += 100;
        UART_println("Blink interval rate decreased");
        UART_print_int(interval);
      }
    }
  };
  
  // Initial press
  if(buttonPressed(button)) {
    changeInterval();
    button.holdTime = 0;
  }
  
  // Button held
  if(!button.currentState) {
    button.holdTime++;
    // Wait before auto-repeat
    if(button.holdTime > 500) {
      // Repeat every 100ms
      if((button.holdTime % 100) == 0) {
        changeInterval();
      }
    }
  } else {
    button.holdTime = 0;
  }
}