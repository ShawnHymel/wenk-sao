#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Make Ports A and B all output
    DDRA = 0b11111111;
    DDRB = 0b11111111;
    
    // Infinite loop
    while(1) //infinite loop
    {
        
        // Turn on all LEDs
        PORTA = 0xFF;
        PORTB = 0xFF; //Turns ON All LEDs
        
        // Wait 1 second
        _delay_ms(1000); //1 second delay
        
        // Turn off all LEDs
        PORTA = 0x00;
        PORTB = 0x00;
        
        // Wait 1 second
        _delay_ms(1000);
    }
}