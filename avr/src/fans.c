// Sets the given fan PWM.

void fan_set_pwm(uint8_t fan, uint8_t pwm) {

    switch (fan) {

        case 0: OCR0A = pwm; break;

        case 1: OCR0B = pwm; break;

        case 2: OCR2A = pwm; break;

        case 3: OCR2B = pwm; break;
    }
}

// Enables the given fan.

void fan_enable(uint8_t fan) {

    switch (fan) {

        case 0: PORTB |= (1 << PB0); break;

        case 1: PORTB |= (1 << PB1); break;

        case 2: PORTB |= (1 << PB2); break;

        case 3: PORTB |= (1 << PB4); break;
    }
}

// Disables the given fan.

void fan_disable(uint8_t fan) {

    fan_set_pwm(fan, 0);

    switch (fan) {

        case 0: PORTB &= ~(1 << PB0); break;

        case 1: PORTB &= ~(1 << PB1); break;

        case 2: PORTB &= ~(1 << PB2); break;

        case 3: PORTB &= ~(1 << PB4); break;
    }
}

// Checks whether the given fan is enabled.

uint8_t fan_enabled(uint8_t fan) {

    switch (fan) {

        case 0: return PORTB & (1 << PB0);

        case 1: return PORTB & (1 << PB1);

        case 2: return PORTB & (1 << PB2);

        case 3: return PORTB & (1 << PB4);
    }

    return 0;
}
