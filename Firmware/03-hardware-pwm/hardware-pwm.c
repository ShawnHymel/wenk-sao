// Need to define clock speed for delay functions
#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    
    // Make only red LED pins output (PA7, PB2)
    DDRA = (1 << 7);
    DDRB = (1 << 2);
    
    // Set Timer 0 to fast PWM
    TCCR0A = (1 << WGM01) | (1 << WGM00);
    
    // Set Compare Output modes for A and B to inverting PWM
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
    TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
    
    // Set prescaler to 1 (no prescaling)
    TCCR0B = (1 << CS00);
    
    // Infinite loop
    while(1) {
        
        int16_t d;
        
        // Increase left eye, decrease right eye
        for ( d = 0; d <= 255; d++ ) {
            OCR0A = (uint8_t)d;         // Left eye
            OCR0B = (uint8_t)255 - d;   // Right eye
            _delay_ms(2);
        }
        
        // Decrease left eye, increase right eye
        for ( d = 255; d >= 0; d-- ) {
            OCR0A = (uint8_t)d;         // Left eye
            OCR0B = (uint8_t)255 - d;   // Right eye
            _delay_ms(2);
        }
    }
}
