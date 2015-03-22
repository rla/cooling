// Control settings are stored
// in the EEPROM memory.

uint8_t EEMEM fan_control[4] = { 0, 0, 0, 0 };

// Sets the given fan PWM.

void fan_set_pwm(uint8_t fan, uint8_t pwm) {

    switch (fan) {

        case 0: OCR0A = pwm; break;

        case 1: OCR0B = pwm; break;

        case 2: OCR2A = pwm; break;

        case 3: OCR2B = pwm; break;
    }
}

// Gets the given fan PWM.

uint8_t fan_get_pwm(uint8_t fan) {

    switch (fan) {

        case 0: return OCR0A;

        case 1: return OCR0B;

        case 2: return OCR2A;

        case 3: return OCR2B;
    }

    return 0;
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

// Returns whether pulse stretch
// is enabled on the given fan.

uint8_t fan_stretch_enabled(uint8_t fan) {

    if (fan > 3) {

        return 0;

    } else {

        uint8_t control[4];

        eeprom_read_block(&control, &fan_control, sizeof(fan_control));

        return control[fan];
    }

    return 0;
}

// Reads stretch data into the given buffer.

void fan_stretch_read_info(uint8_t *buffer) {

    eeprom_read_block(buffer, &fan_control, sizeof(fan_control));
}

// Enables pulse stretch on the given fan.

void fan_stretch_enable(uint8_t fan) {

    if (fan < 4) {

        uint8_t control[4];

        eeprom_read_block(&control, &fan_control, sizeof(fan_control));

        control[fan] = 1;

        eeprom_update_block(control, &fan_control, sizeof(fan_control));
    }
}

// Disables pulse stretch on the given fan.

void fan_stretch_disable(uint8_t fan) {

    if (fan < 4) {

        uint8_t control[4];

        eeprom_read_block(&control, &fan_control, sizeof(fan_control));

        control[fan] = 0;

        eeprom_update_block(control, &fan_control, sizeof(fan_control));
    }
}
