#define USART_COMMAND_END 0

#define USART_COMMAND_ADC_0 1
#define USART_COMMAND_ADC_1 2

#define USART_COMMAND_GET_RPM_0 3
#define USART_COMMAND_GET_RPM_1 4
#define USART_COMMAND_GET_RPM_2 5
#define USART_COMMAND_GET_RPM_3 6

#define USART_COMMAND_SET_PWM_0 7
#define USART_COMMAND_SET_PWM_1 8
#define USART_COMMAND_SET_PWM_2 9
#define USART_COMMAND_SET_PWM_3 10

#define USART_COMMAND_GET_PWM_0 11
#define USART_COMMAND_GET_PWM_1 12
#define USART_COMMAND_GET_PWM_2 13
#define USART_COMMAND_GET_PWM_3 14

#define USART_COMMAND_ENABLE_0 15
#define USART_COMMAND_ENABLE_1 16
#define USART_COMMAND_ENABLE_2 17
#define USART_COMMAND_ENABLE_3 18

#define USART_COMMAND_DISABLE_0 19
#define USART_COMMAND_DISABLE_1 20
#define USART_COMMAND_DISABLE_2 21
#define USART_COMMAND_DISABLE_3 22

#define USART_COMMAND_OK 255

volatile uint8_t usart_send_buffer[10];
volatile uint8_t usart_send_buffer_length = 0;
volatile uint8_t usart_send_buffer_pos = 0;

volatile uint8_t usart_recv_buffer[10];
volatile uint8_t usart_recv_buffer_length = 0;

// Puts byte into the USART buffer.

void usart_send_buffer_write(uint8_t byte) {

    usart_send_buffer[usart_send_buffer_length] = byte;
    usart_send_buffer_length += 1;
}

// Sends one byte through USART.
// Sends until all bytes in the buffer
// have been sent.

void usart_send_buffer_send() {

    if (usart_send_buffer_pos < usart_send_buffer_length) {

        UDR0 = usart_send_buffer[usart_send_buffer_pos];
        usart_send_buffer_pos += 1;

    } else {

        usart_send_buffer_length = 0;
        usart_send_buffer_pos = 0;
    }
}

// Puts byte into receive buffer.

void usart_recv_buffer_write(uint8_t byte) {

    if (usart_recv_buffer_length < 10) {

        usart_recv_buffer[usart_recv_buffer_length] = byte;
        usart_recv_buffer_length += 1;
    }
}

// Runs given command and writes response
// data into the buffer.

void do_usart_command() {

    uint8_t command = usart_recv_buffer[0];

    switch (command) {

        case USART_COMMAND_ADC_0:

            usart_send_buffer_write(temperature_0);

        break;

        case USART_COMMAND_ADC_1:

            usart_send_buffer_write(temperature_1);

        break;

        case USART_COMMAND_GET_RPM_0:

            usart_send_buffer_write((uint8_t) (rpm_0 >> 8));
            usart_send_buffer_write((uint8_t) rpm_0);

        break;

        case USART_COMMAND_GET_RPM_1:

            usart_send_buffer_write((uint8_t) (rpm_1 >> 8));
            usart_send_buffer_write((uint8_t) rpm_1);

        break;

        case USART_COMMAND_GET_RPM_2:

            usart_send_buffer_write((uint8_t) (rpm_2 >> 8));
            usart_send_buffer_write((uint8_t) rpm_2);

        break;

        case USART_COMMAND_GET_RPM_3:

            usart_send_buffer_write((uint8_t) (rpm_3 >> 8));
            usart_send_buffer_write((uint8_t) rpm_3);

        break;

        case USART_COMMAND_SET_PWM_0:

            fan_set_pwm(0, usart_recv_buffer[1]);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_SET_PWM_1:

            fan_set_pwm(1, usart_recv_buffer[1]);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_SET_PWM_2:

            fan_set_pwm(2, usart_recv_buffer[1]);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_SET_PWM_3:

            fan_set_pwm(3, usart_recv_buffer[1]);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_ENABLE_0:

            fan_enable(0);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_ENABLE_1:

            fan_enable(1);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_ENABLE_2:

            fan_enable(2);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_ENABLE_3:

            fan_enable(3);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_DISABLE_0:

            fan_disable(0);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_DISABLE_1:

            fan_disable(1);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_DISABLE_2:

            fan_disable(2);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;

        case USART_COMMAND_DISABLE_3:

            fan_disable(3);
            usart_send_buffer_write(USART_COMMAND_OK);

        break;
    }
}

ISR(USART_RX_vect) {

    uint8_t recv = UDR0;

    // Only execute command when
    // data from old commands has been
    // fully sent.

    if (usart_send_buffer_length == 0) {

        if (recv == USART_COMMAND_END) {

            do_usart_command();

            // Reset receive buffer.

            usart_recv_buffer_length = 0;

            // Send data.

            usart_send_buffer_send();

        } else {

            // Accumulate data.

            usart_recv_buffer_write(recv);
        }
    }
}

ISR(USART_TX_vect) {

    // When byte is sent, try send more.

    usart_send_buffer_send();
}
