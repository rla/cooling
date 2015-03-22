// For usart.

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// Port B is output.

void init_port_b() {

    DDRB = 0xFF;
}

// Port C is input.
// PC2-PC5 have pull-ups.

void init_port_c() {

    DDRC = 0x00;
    PORTC |= (1 << PC2);
    PORTC |= (1 << PC3);
    PORTC |= (1 << PC4);
    PORTC |= (1 << PC5);
}

// Port D is output.

void init_port_d() {

    DDRD = 0xFF;
}

// Enable phase-correct PWM mode (p. 105)
// No prescaler. Frequency: fclkIO/510.

void init_timer_0() {

    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B = (1 << CS00);
}

void init_timer_1() {

    // Prescaler 256 (12Mhz / 256 = 46.8kHz).
    // Single overflow period ~ 1.4s.

    TCCR1B = (1 << CS12);

    // Enable interrupt on overflow
    // and compare-match A.

    TIMSK1 = (1 << TOIE1) | (1 << OCIE1A);

    // Set timeout compare
    // for compare-match A. This is used
    // for RPM measurement timeout.

    OCR1A = 32000;
}

// Enable phase-correct PWM mode.
// No prescaler. Frequency: fclkIO/510 (p. 144).

void init_timer_2() {

    // Clear OC2A on Compare Match when up-counting. Set OC2A on
    // Compare Match when down-counting.
    // Clear OC2B on Compare Match when up-counting. Set OC2B on
    // Compare Match when down-counting.

    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
    TCCR2B = (1 << CS20);
}

void init_usart() {

    // Enable receiver and transmitter.

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set baud rate.

    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;

    // Enable interrupt on receive and send.

    UCSR0B |= (1 << RXCIE0) | (1 << TXCIE0);

    // FIXME tri-state, internal pull-up.
}

void init_adc() {

    // ADC is using internal 1.1V reference.
    // AVcc could be off from 5V

    ADMUX |= (1 << REFS0) | (1 << REFS1);

    // Enables ADC.

    ADCSRA |= (1 << ADEN);

    // Enables ADC interrupt.

    ADCSRA |= (1 << ADIE);

    // Set ADC clock division to 128.
    // This gives 93.75kHz as ADC clock.

    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    // Disable digital inputs on ADC0 and ADC1

    DIDR0 |= (1 << ADC0D) | (1 << ADC1D);
}

// The main initialization routine.
// Also enables interrupts.

void init() {

    init_port_b();
    init_port_c();
    init_port_d();
    init_timer_0();
    init_timer_1();
    init_timer_2();
    init_usart();
    init_adc();
	sei();
}
