#ifndef HELPERS_H
#define HELPERS_H

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

struct Button {
    bool currentState;
    bool lastState;
    uint16_t holdTime;
};

void UART_init(uint16_t baud);
void UART_transmit(char data);
void UART_print(const char* str);
void UART_println(const char* str);
void UART_print_int(uint32_t number);

bool buttonPressed(const Button& button);
void updateButton(Button& button, volatile uint8_t& pinRegister, uint8_t pin);
void adjustInterval(Button& button, uint16_t& interval, bool increase);

#endif