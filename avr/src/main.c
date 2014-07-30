#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <util/crc16.h>

/*
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
}*/

#include "init.c"
#include "fans.c"
#include "init_fans.c"
#include "adc.c"
#include "measure.c"
#include "rpm.c"
#include "adjust.c"
#include "error.c"
#include "hex.c"
#include "usart_buffer.c"
#include "pearson.c"
#include "protocol.c"
#include "usart_run.c"

int main() {

    init();
    init_fans(0);

    uint8_t start_wait = 0;

    while (1) {

        if (!measure_timeout) {

            rpm_measure();

            if (!measure_timeout) {

                measure_timeout = 1;
            }

            // Wait some time before enabling
            // the adjustment algorithm.

            if (start_wait < 10) {

                start_wait += 1;

            } else {

                adjust();

                check_error();
            }
        }
    };

    return 1;
}
