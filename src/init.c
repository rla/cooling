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
// No prescaler. Frequency: fclkIO/510

void init_timer_0() {

    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B = (1 << CS00);
}

void init_timer_1() {

}

void init_timer_2() {

}

void init_usart() {

}

void init_adc() {

}

// The main initialization routine.

void init() {

    init_port_b();
    init_port_c();
    init_port_d();
    init_timer_0();
    init_timer_1();
    init_timer_2();
    init_usart();
    init_adc();
}
