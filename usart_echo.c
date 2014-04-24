#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// See p. 181

void init_usart() {
    
    // Enable receiver and transmitter.
    
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set baud rate.
    
    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;
    
    // Enable interrupt on receive.
    
    UCSR0B |= (1 << RXCIE0);
}

ISR(USART_RX_vect) {
    
    char data;
    
    data = UDR0;
    
    UDR0 = data;
}

int main (void) {
    
    init_usart();
    
    sei();

    while (1) {}
}
