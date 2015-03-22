#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/eeprom.h>

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
