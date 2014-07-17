volatile uint16_t rpm_0 = 0;
volatile uint16_t rpm_1 = 0;
volatile uint16_t rpm_2 = 0;
volatile uint16_t rpm_3 = 0;

volatile uint8_t rpm_fan = 0;

// Waits for high signal on
// the current fan's RPM input pin.

void rpm_wait_high() {

    switch (rpm_fan) {

        case 0: while (!measure_timeout && (PINC & (1 << PC2))); break;

        case 1: while (!measure_timeout && (PINC & (1 << PC3))); break;

        case 2: while (!measure_timeout && (PINC & (1 << PC4))); break;

        case 3: while (!measure_timeout && (PINC & (1 << PC5))); break;
    }
}

// Waits for low signal on
// the current fan's RPM input pin.

void rpm_wait_low() {

    switch (rpm_fan) {

        case 0: while (!measure_timeout && !(PINC & (1 << PC2))); break;

        case 1: while (!measure_timeout && !(PINC & (1 << PC3))); break;

        case 2: while (!measure_timeout && !(PINC & (1 << PC4))); break;

        case 3: while (!measure_timeout && !(PINC & (1 << PC5))); break;
    }
}

// Waits for rising signal on
// the current fan's RPM input pin.

void rpm_wait_rising() {

    rpm_wait_low();

    if (measure_timeout) {

        return;
    }

    rpm_wait_high();
}

// Updates the current fan's RPM value.

void rpm_update(uint16_t rpm) {

    switch (rpm_fan) {

        case 0: rpm_0 = rpm; break;

        case 1: rpm_1 = rpm; break;

        case 2: rpm_2 = rpm; break;

        case 3: rpm_3 = rpm; break;
    }
}

// Starts RPM measurement.
// Fans are alternatively selected.

void rpm_measure() {

    // Selects next fan.

    rpm_fan = (rpm_fan + 1) % 4;

    // Resets RPM to 0.

    rpm_update(0);

    uint16_t start;

    // Wait for first rising.

    rpm_wait_rising();

    if (measure_timeout) {

        return;
    }

    start = TCNT1;

    // Wait for second risin.

    rpm_wait_rising();

    if (measure_timeout) {

        return;
    }

    // Calculates RPM.

    uint16_t count = TCNT1 - start;

    // Updates with the new value.
    // FIXME bring out constants

    rpm_update(60 / (count * 0.00002133 * 2));
}
