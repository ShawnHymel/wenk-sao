#include <avr/io.h>
#include <avr/interrupt.h>

// Timer values (1 sec with prescaler of 64)
const uint16_t t1_load = 0;
const uint16_t t1_comp = 15625;

int main(void) {
    
    // Make only red LED pins output (PA7, PB2)
    DDRA = (1 << 7);
    DDRB = (1 << 2);
    
    // Set Timer 1 to normal operation
    TCCR1A = 0;
    TCCR1B = 0;
    
    // Set prescaler to 64
    TCCR1B |= (1 << CS11) | (1 << CS10);
    
    // Reset Timer 1 and set compare values
    TCNT1 = t1_load;
    OCR1A = t1_comp;
    
    // Enable Timer 1 compare interrupt
    TIMSK1 = (1 << OCIE1A);
    
    // Enable global interrupts
    sei();
    
    // Infinite loop
    while(1) {
        // Do nothing
    }
}

// Interrupt service routine
ISR(TIM1_COMPA_vect) {
    
    // Reset Timer 1
    TCNT1 = t1_load;
    
    // Toggle red LEDs
    PORTA ^= (1 << 7);
    PORTB ^= (1 << 2);
}
