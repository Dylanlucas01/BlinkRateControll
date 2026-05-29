#include <avr/io.h>
#include <util/delay.h>
#include "helpers.h"

void ledBlink(bool& blinkState, uint16_t& interval);

int main() {
  UART_init(9600);

  DDRB |= (1 << PB5); // Set PB5 (digital pin 13) as output
  DDRD &= ~(1 << PD2) | (1 << PD4) | (1 << PD7); // Set PD2/4/7 (digital pin 2/4/7) as input

  PORTD |= (1 << PD2) | (1 << PD4) | (1 << PD7); // Enable pull-up resistor

  bool blinkState = false;

  uint16_t interval = 1000; // Initial blink interval in milliseconds

  // Button structs
  Button toggleButton {true, true, 0};
  Button increaseButton {true, true, 0};
  Button decreaseButton {true, true, 0};

  while(true) {
    // Update button states
    updateButton(toggleButton, PIND, PD2);

    updateButton(increaseButton, PIND, PD4);

    updateButton(decreaseButton, PIND, PD7);

    // Toggle blinking
    if(buttonPressed(toggleButton)) {
        blinkState = !blinkState;
        UART_println(blinkState ? "Blinking started" : "Blinking stopped");
    }
    
    // Adjust blink interval
    adjustInterval(increaseButton, interval, true);

    adjustInterval(decreaseButton, interval, false);

    // LED blinking
    if(blinkState) {
        ledBlink(blinkState, interval);
    } else {
        PORTB &= ~(1 << PB5);
    }
  }
}

void ledBlink(bool& blinkState, uint16_t& interval) {
  static uint32_t lastToggle = 0;
  static bool ledState = false;
  static uint32_t blinkCount = 0;

  _delay_ms(1);

  lastToggle++;

  if(lastToggle >= interval) {
    lastToggle = 0;
    ledState = !ledState;
    blinkCount++;

    if(ledState) {
      PORTB |= (1 << PB5);
      UART_println("LED toggled ON");
    } else {
        PORTB &= ~(1 << PB5);
        UART_println("LED toggled OFF");
    }

    UART_println("Blink Count:");
    UART_print_int(blinkCount);
  }
}