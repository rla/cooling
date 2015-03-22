volatile uint16_t rpm_0 = 0;
volatile uint16_t rpm_1 = 0;
volatile uint16_t rpm_2 = 0;
volatile uint16_t rpm_3 = 0;

// Waits for high signal on
// the current fan's RPM input pin.

void rpm_wait_high(uint8_t fan) {

    switch (fan) {

        case 0: while (!measure_timeout && (PINC & (1 << PC2))); break;

        case 1: while (!measure_timeout && (PINC & (1 << PC3))); break;

        case 2: while (!measure_timeout && (PINC & (1 << PC4))); break;

        case 3: while (!measure_timeout && (PINC & (1 << PC5))); break;
    }
}

// Waits for low signal on
// the current fan's RPM input pin.

void rpm_wait_low(uint8_t fan) {

    switch (fan) {

        case 0: while (!measure_timeout && !(PINC & (1 << PC2))); break;

        case 1: while (!measure_timeout && !(PINC & (1 << PC3))); break;

        case 2: while (!measure_timeout && !(PINC & (1 << PC4))); break;

        case 3: while (!measure_timeout && !(PINC & (1 << PC5))); break;
    }
}

// Waits for rising signal on
// the current fan's RPM input pin.

void rpm_wait_rising(uint8_t fan) {

    rpm_wait_low(fan);

    if (measure_timeout) {

        return;
    }

    rpm_wait_high(fan);
}

// Updates the current fan's RPM value.

void rpm_update(uint8_t fan, uint16_t rpm) {

    switch (fan) {

        case 0: rpm_0 = rpm; break;

        case 1: rpm_1 = rpm; break;

        case 2: rpm_2 = rpm; break;

        case 3: rpm_3 = rpm; break;
    }
}

void rpm_measure_fan(uint8_t fan) {

    // Resets RPM to 0.

    rpm_update(fan, 0);

    uint16_t start;

    // Wait for first rising.

    rpm_wait_rising(fan);

    if (measure_timeout) {

        return;
    }

    start = TCNT1;

    // Wait for second risin.

    rpm_wait_rising(fan);

    if (measure_timeout) {

        return;
    }

    // Calculates RPM.

    uint16_t count = TCNT1 - start;

    // See init.c for Timer 1.
    // 46.8 kHz tick rate gives period 0.00002133.
    // Fan does 2 pulses per rotation.

    rpm_update(fan, 60 / (count * 0.00002133 * 2));
}

volatile uint8_t rpm_fan = 0;

// Starts RPM measurement.
// Fans are alternatively selected.

void rpm_measure() {

    uint8_t old = 0;

    // Selects next fan.

    rpm_fan = (rpm_fan + 1) % 4;

    if (fan_stretch_enabled(rpm_fan)) {

        // Pulse stretch enabled.

        old = fan_get_pwm(rpm_fan);

        fan_set_pwm(rpm_fan, 255);
    }

    rpm_measure_fan(rpm_fan);

    if (fan_stretch_enabled(rpm_fan)) {

        fan_set_pwm(rpm_fan, old);
    }
}
