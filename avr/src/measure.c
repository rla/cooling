// Flag that is set when measurement
// timeout occurs.

volatile uint8_t measure_timeout = 0;

// Which fan to measure.

// Timeout flag is cleared on each overflow.

ISR(TIMER1_OVF_vect) {

    measure_timeout = 0;

    // Start ADC measurement.

    adc_measure();
}

// Timeout flag is set on the COMPA overflow.

ISR(TIMER1_COMPA_vect) {

    measure_timeout = 1;
}
