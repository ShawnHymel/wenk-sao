/**
 * Title: Rainbow Pattern
 * Author: Shawn Hymel
 * Date: November 2, 2011
 *
 * Create a rainbow pattern on the eyes of the Wenk SAO board.
 * Compiled for ATtiny84A.
 * 
 * Note: You will need to remove the internal clock divider (div 8) fuse to make
 *       the LEDs appear steady. Use the following:
 *          $ avrdude -c usbtiny -p t84 -U lfuse:w:0xE2:m
 *
 * Beerware: As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */

// Need to define clock speed for delay functions
#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Function declarations
void leftWheel(uint8_t wheel_pos);
void rightWheel(uint8_t wheel_pos);

// Rainbow offset
const uint8_t left_offset = 40;
const uint8_t right_offset = 0;

// Timer values
const uint8_t t0_load = 0;
const uint8_t t0_comp = 65; // ~60 Hz PWM

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
    
    // Set prescaler to 8
    TCCR0B |= (1 << CS01);
    
    // Reset Timer 0 and set compare values
    TCNT0 = t0_load;
    OCR0A = t0_comp;
    
    // Enable Timer 0 compare interrupt
    TIMSK0 = (1 << OCIE0A);
    
    // Enable global interrupts
    sei();
    
    // Infinite loop
    while(1) {
        for ( uint16_t i = 0; i < 256; i++ ) {
            leftWheel((i + left_offset) % 255);
            rightWheel((i + right_offset) % 255);
            _delay_ms(10);
        }
    }
}

// Set left eye to color based on input wheel position (0..255)
// Based on https://codebender.cc/sketch:80438#Neopixel%20Rainbow.ino
void leftWheel(uint8_t wheel_pos) {
    if ( wheel_pos < 85 ) {
        left_r = wheel_pos * 3;
        left_g = 255 - (wheel_pos * 3);
        left_b = 0;
    } else if ( wheel_pos < 170 ) {
        wheel_pos -= 85;
        left_r = 255 - (wheel_pos * 3);
        left_g = 0;
        left_b = wheel_pos * 3;
    } else{
        wheel_pos -= 170;
        left_r = 0;
        left_g = wheel_pos * 3;
        left_b = 255 - (wheel_pos * 3);
    }
}

// Set right eye to color based on input wheel position (0..255)
// Based on https://codebender.cc/sketch:80438#Neopixel%20Rainbow.ino
void rightWheel(uint8_t wheel_pos) {
    if ( wheel_pos < 85 ) {
        right_r = wheel_pos * 3;
        right_g = 255 - (wheel_pos * 3);
        right_b = 0;
    } else if ( wheel_pos < 170 ) {
        wheel_pos -= 85;
        right_r = 255 - (wheel_pos * 3);
        right_g = 0;
        right_b = wheel_pos * 3;
    } else{
        wheel_pos -= 170;
        right_r = 0;
        right_g = wheel_pos * 3;
        right_b = 255 - (wheel_pos * 3);
    }
}

// Interrupt service routine
ISR(TIM0_COMPA_vect) {
    
    // Reset Timer 0
    TCNT0 = t0_load;
    
    // Increment counter (just let roll over)
    ticks++;
    
    // Save ticks to local variable to save RAM lookup cycles
    uint8_t t = ticks;
    
    // Set left LED based on duty cycle
    if ( t < left_r ) {
        PORTB &= ~(1 << p_lr); // LED on
    } else {
        PORTB |= (1 << p_lr);  // LED off
    }
    if ( t < left_g ) {
        PORTB &= ~(1 << p_lg); // LED on
    } else {
        PORTB |= (1 << p_lg);  // LED off
    }
    if ( t < left_b ) {
        PORTB &= ~(1 << p_lb); // LED on
    } else {
        PORTB |= (1 << p_lb);  // LED off
    }
    
    // Set right LED based on duty cycle
    if ( t < right_r ) {
        PORTA &= ~(1 << p_rr); // LED on
    } else {
        PORTA |= (1 << p_rr);  // LED off
    }
    if ( t < right_g ) {
        PORTA &= ~(1 << p_rg); // LED on
    } else {
        PORTA |= (1 << p_rg);  // LED off
    }
    if ( t < right_b ) {
        PORTA &= ~(1 << p_rb); // LED on
    } else {
        PORTA |= (1 << p_rb);  // LED off
    }
}
