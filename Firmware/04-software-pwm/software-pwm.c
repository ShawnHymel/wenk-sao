#include <avr/io.h>
#include <avr/interrupt.h>

// Timer values
const uint8_t t0_load = 0;
const uint8_t t0_comp = 78; // ~50 Hz PWM

// LED pins (left = PORTB, right = PORTA)
const uint8_t p_lr = 2;
const uint8_t p_lg = 0;
const uint8_t p_lb = 1;
const uint8_t p_rr = 7;
const uint8_t p_rg = 2;
const uint8_t p_rb = 3;

// Tick counter
volatile uint8_t ticks = 0;

// Duty cycle per color
volatile uint8_t left_r = 0;
volatile uint8_t left_g = 0;
volatile uint8_t left_b = 0;
volatile uint8_t right_r = 0;
volatile uint8_t right_g = 0;
volatile uint8_t right_b = 0;

// Program entry point
int main(void) {
    
    // Make LED pins output
    DDRA = (1 << p_rr) | (1 << p_rg) | (1 << p_rb);
    DDRB = (1 << p_lr) | (1 << p_lg) | (1 << p_lb);
    
    // Set Timer 0 to normal operation
    TCCR0A = 0;
    TCCR0B = 0;
    
    // Set prescaler to 1
    TCCR0B |= (1 << CS00);
    
    // Reset Timer 0 and set compare values
    TCNT0 = t0_load;
    OCR0A = t0_comp;
    
    // Enable Timer 0 compare interrupt
    TIMSK0 = (1 << OCIE0A);
    
    // Enable global interrupts
    sei();
    
    // Infinite loop
    while(1) {
        
        // Set left eye: orange
        left_r = 255;
        left_g = 30;
        left_b = 0;
        
        // Set right eye: teal
        right_r = 0;
        right_g = 128;
        right_b = 128;
    }
}

// Interrupt service routine
ISR(TIM0_COMPA_vect) {
    
    // Reset Timer 0
    TCNT0 = t0_load;
    
    // Increment counter (just let roll over)
    ticks++;
    
    // Set left LED based on duty cycle
    if ( ticks < left_r ) {
        PORTB &= ~(1 << p_lr); // LED on
    } else {
        PORTB |= (1 << p_lr);  // LED off
    }
    if ( ticks < left_g ) {
        PORTB &= ~(1 << p_lg); // LED on
    } else {
        PORTB |= (1 << p_lg);  // LED off
    }
    if ( ticks < left_b ) {
        PORTB &= ~(1 << p_lb); // LED on
    } else {
        PORTB |= (1 << p_lb);  // LED off
    }
    
    // Set right LED based on duty cycle
    if ( ticks < right_r ) {
        PORTA &= ~(1 << p_rr); // LED on
    } else {
        PORTA |= (1 << p_rr);  // LED off
    }
    if ( ticks < right_g ) {
        PORTA &= ~(1 << p_rg); // LED on
    } else {
        PORTA |= (1 << p_rg);  // LED off
    }
    if ( ticks < right_b ) {
        PORTA &= ~(1 << p_rb); // LED on
    } else {
        PORTA |= (1 << p_rb);  // LED off
    }
}
