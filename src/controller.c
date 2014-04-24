#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

// Set 0 to disable USART.

#define ENABLE_USART 1

// Set 0 to disable ADC channel(s).

#define ENABLE_ADC_1 1
#define ENABLE_ADC_2 1

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// See p. 181

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

void init_fans() {

}

volatile float temp1 = 0;
volatile float temp2 = 0;

void init_adc() {

    if (ENABLE_ADC_1) {

    } else {

        // FIXME tri-state, internal pull-up.
    }

    if (ENABLE_ADC_2) {

    } else {

        // FIXME tri-state, internal pull-up.
    }

    temp1 = 0;
    temp2 = 0;
}

// Initializes PWM channels 1 and 2.
// Timer0 (8 bits) is used for it.
// PWM channel 1 is OC0A
// PWM channel 2 is 0C0B
// PWM frequency is 31kHz.

void init_pwm_1_2() {

    // Make PD5 and PD6 output (p. 91).

    DDRD |= (1 << DDB5) | (1 << DDB6);

    // Enable phase-correct PWM mode (p. 105)

    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);

    // No prescaler. Frequency: fclkIO/510

    TCCR0B = (1 << CS00);
}

// Sets PWM channel 1 value.

void set_pwm_1(unsigned char value) {

    // See p. 108.

    OCR0A = value;
}

// Sets PWM channel 2 value.

void set_pwm_2(unsigned char value) {

    // See p. 108.

    OCR0B = value;
}

// Initializes Timer1 for
// measuring RPM.
// Timer1 should run at 250kHz
// No port operation.
// RPM inputs:
// RPM1: PC0 (PCINT8)
// RPM2: PC1 (PCINT9)
// RPM3: PC2 (PCINT10)
// RPM4: PC3 (PCINT11)

void init_rpm_check() {

    // Prescaler 256 (16Mhz / 256 = 62.5kHz).
    // Single overflow period ~ 1.04s.

    TCCR1B = (1 << CS12);

    // Enable interrupt on overflow.

    TIMSK1 = (1 << TOIE1) | (1 << OCIE1A);

    // Set 1024 as timeout compare.

    OCR1A = 32000;

    // PC0 as input.

    DDRC &= ~(1 << PC0);
}

volatile uint8_t timeout = 0;

// Timer 1 overflow interrupt handling.

ISR(TIMER1_OVF_vect) {

    timeout = 0;
}

// On COMPA overflow set timeout flag.

ISR(TIMER1_COMPA_vect) {

    timeout = 1;
}

void wait_low() {

    while (!timeout && (PINC & (1 << PC0)));
}

void wait_high() {

    while (!timeout && !(PINC & (1 << PC0)));
}

volatile uint16_t rpm = 0;

void measure() {

    // Pulse stretching.

    uint8_t old = OCR0A;

    // FIXME commented out
    //OCR0A = 255;

    _delay_ms(5);

    uint16_t start;

    wait_low();

    if (timeout) {

        OCR0A = old;
        rpm = 0;
        return;
    }

    wait_high();

    if (timeout) {

        OCR0A = old;
        rpm = 0;
        return;
    }

    start = TCNT1;

    wait_low();

    if (timeout) {

        OCR0A = old;
        rpm = 0;
        return;
    }

    wait_high();

    if (timeout) {

        OCR0A = old;
        rpm = 0;
        return;
    }

    // Find Timer 1 between two
    // raising fronts.

    uint16_t count = TCNT1 - start;

    //

    rpm = 60 / (count * 0.000016 * 2);

    // Restore PWM.

    OCR0A = old;
}

volatile uint16_t rpm_copy = 0;
volatile uint8_t sent = 0;

ISR(USART_RX_vect) {

    char data;

    data = UDR0;

    rpm_copy = rpm;

    sent = 0;

    UDR0 = (rpm_copy >> 8);
}

ISR(USART_TX_vect) {

    if (!sent) {

        UDR0 = rpm_copy;
    }

    sent = 1;
}

volatile uint16_t target_rpm = 300;

void maintain_rpm() {

    uint8_t pwm = OCR0A;

    if (target_rpm > rpm) {

        pwm += 10;

        if (pwm < OCR0A) {

            // Overflow.

            pwm = 255;
        }

    } else {

        pwm -= 10;

        if (pwm > OCR0A) {

            // Underflow.

            pwm = 10;
        }
    }

    OCR0A = pwm;
}

int main() {

    DDRD |= (1 << DD7);

        PORTD |= (1 << PD7);

    _delay_ms(10);

    PORTD &= ~(1 << PD7);

    init_pwm_1_2();

    set_pwm_1(255);

    init_rpm_check();

    init_usart();

    sei();

    while (1) {

        if (!timeout) {

            measure();

            if (!timeout) {

                timeout = 1;
            }

            maintain_rpm();
        }
    }

    return 1;
}
