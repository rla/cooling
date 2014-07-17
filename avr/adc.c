#define ADC_REFERENCE 1.1
#define ADC_OFFSET 0.5

volatile uint8_t temperature_0 = 0;
volatile uint8_t temperature_1 = 0;

// Starts measurement.
// Sensor 1 is ADC0
// Sensor 2 is ADC1

void adc_measure_channel(uint8_t channel) {

    // Clears MUX0..3 bits.

    ADMUX &= 0xF0;

    // Sets MUX0..3 bits from channel value.

    ADMUX |= 0x0F & channel;

    // Starts measurement.

    ADCSRA |= (1 << ADSC);
}

// Returns currently selected channel.

uint8_t adc_channel() {

    return ADMUX & 0x0F;
}

// Handles conversion completion.
// Starts new conversion if not all
// channels have not been measured.

ISR(ADC_vect) {

    uint8_t channel = adc_channel();

    uint16_t adc = ADC;

    float voltage = ((float) adc / 1024) * ADC_REFERENCE;

    uint8_t temperature = (voltage - ADC_OFFSET) / 0.01;

    if (channel == 0) {

        temperature_0 = temperature;

        adc_measure_channel(channel + 1);

    } else {

        temperature_1 = temperature;
    }
}

// Starts measurement.
// One measurement cycle
// takes about 1ms.

void adc_measure() {

    adc_measure_channel(0);
}
