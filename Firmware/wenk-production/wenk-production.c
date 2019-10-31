#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    
    // Make PA2/3/7 and PB0/1/2 output
    DDRA |= 0b10001100;
    DDRB |= 0b00000111;
    
    // Turn off LEDs by default
    PORTA |= 0b10001100;
    PORTB |= 0b00000111;
    
    // Flash through colors a few times
    for ( uint8_t i = 0; i < 5; i++ ) {
        
        // Turn off blue
        PORTA |= (1 << 3);
        PORTB |= (1 << 1);
        
        // Turn on red
        PORTA &= ~(1 << 7);
        PORTB &= ~(1 << 2);
        _delay_ms(500);
        
        // Turn off red
        PORTA |= (1 << 7);
        PORTB |= (1 << 2);
        
        // Turn on green
        PORTA &= ~(1 << 2);
        PORTB &= ~(1 << 0);
        _delay_ms(500);
        
        // Turn off green
        PORTA |= (1 << 2);
        PORTB |= (1 << 0);
        
        // Turn on blue
        PORTA &= ~(1 << 3);
        PORTB &= ~(1 << 1);
        _delay_ms(500);
    }
    
    // Turn on all (white)
    PORTA &= ~((1 << 7) | (1 << 2) | (1 << 3));
    PORTB &= ~((1 << 2) | (1 << 0) | (1 << 1));
    
    // Do nothing
    while (1);
}