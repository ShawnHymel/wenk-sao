// Need to define clock speed for delay functions
#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    
    // Make Ports A and B all output
    DDRA = 0b11111111;
    DDRB = 0b11111111;
    
    // Infinite loop
    while(1) {
        
        // Turn on all LEDs
        PORTA = 0x00;
        PORTB = 0x00;
        
        // Wait 1 second
        _delay_ms(1000);
        
        // Turn off all LEDs
        PORTA = 0xFF;
        PORTB = 0xFF;
        
        // Wait 1 second
        _delay_ms(1000);
    }
}
