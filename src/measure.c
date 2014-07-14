// Flag that is set when measurement
// timeout occurs.

volatile uint8_t measure_timeout = 0;

// Timeout flag is cleared on each overflow.

ISR(TIMER1_OVF_vect) {

    measure_timeout = 0;
}

// Timeout flag is set on the COMPA overflow.

ISR(TIMER1_COMPA_vect) {

    measure_timeout = 1;
}

// Waits for high signal on
// fan's RPM input pin.

void wait_high(uint8_t fan) {

    uint8_t pin = fans[fan].pin_rpm;

    while (!measure_timeout && (PINC & (1 << pin)));
}

// Waits for low signal on
// fan's RPM input pin.

void wait_low(uint8_t fan) {

    uint8_t pin = fans[fan].pin_rpm;

    while (!measure_timeout && !(PINC & (1 << pin)));
}

// Waits for rising signal on
// fan's RPM input pin.

void wait_rising(uint8_t fan) {

    wait_low(fan);

    if (measure_timeout) {

        return;
    }

    wait_high(fan);
}

// Measures fan 1 RPM.

void measure_fan(uint8_t fan) {

    // Reset PWM.

    fans[fan].rpm = 0;

    uint16_t start;

    // Wait for first rising.

    wait_rising(fan);

    if (measure_timeout) {

        return;
    }

    start = TCNT1;

    // Wait for second risin.

    wait_rising(fan);

    if (measure_timeout) {

        return;
    }

    // Calculate RPM.

    uint16_t count = TCNT1 - start;

    // FIXME adjust to 12MHz crystal.

    fans[fan].rpm = 60 / (count * 0.000016 * 2);
}
