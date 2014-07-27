#define COMMAND_ADC_0 1
#define COMMAND_ADC_1 2

#define COMMAND_GET_RPM_0 3
#define COMMAND_GET_RPM_1 4
#define COMMAND_GET_RPM_2 5
#define COMMAND_GET_RPM_3 6

#define COMMAND_SET_PWM_0 7
#define COMMAND_SET_PWM_1 8
#define COMMAND_SET_PWM_2 9
#define COMMAND_SET_PWM_3 10

#define COMMAND_GET_PWM_0 11
#define COMMAND_GET_PWM_1 12
#define COMMAND_GET_PWM_2 13
#define COMMAND_GET_PWM_3 14

#define COMMAND_ENABLE_0 15
#define COMMAND_ENABLE_1 16
#define COMMAND_ENABLE_2 17
#define COMMAND_ENABLE_3 18

#define COMMAND_DISABLE_0 19
#define COMMAND_DISABLE_1 20
#define COMMAND_DISABLE_2 21
#define COMMAND_DISABLE_3 22

#define COMMAND_ECHO 254

#define RESPONSE_OK 255
#define RESPONSE_FAIL 254
#define RESPONSE_CHECKSUM_FAIL 253

// Must be <= USART_BUFFER_SIZE

#define PROTOCOL_BUFFER_SIZE 10

volatile uint8_t protocol_recv_buffer[PROTOCOL_BUFFER_SIZE];
volatile uint8_t protocol_recv_buffer_length = 0;

volatile uint8_t protocol_send_buffer[PROTOCOL_BUFFER_SIZE];
volatile uint8_t protocol_send_buffer_length = 0;

// Resets the send buffer.

void protocol_send_buffer_reset() {

    protocol_send_buffer_length = 0;
}

// Puts byte into send buffer.

void protocol_send_buffer_put(uint8_t byte) {

    if (protocol_send_buffer_length < PROTOCOL_BUFFER_SIZE) {

        protocol_send_buffer[protocol_send_buffer_length] = byte;
        protocol_send_buffer_length += 1;
    }
}

// Adds Pearson hash value into sending buffer.
// FIXME rename

void protocol_send_buffer_put_crc() {

    protocol_send_buffer_put(pearson_hash(
        protocol_send_buffer, 0, protocol_send_buffer_length));
}

// Verifies the checksum of currently
// received data.

uint8_t protocol_verify() {

    // Checksum is the last received byte.

    uint8_t check = protocol_recv_buffer[protocol_recv_buffer_length - 1];

    return check == pearson_hash(
        protocol_recv_buffer, 0, protocol_recv_buffer_length - 1);
}

// Runs the decoded command.

void protocol_command_run() {

    uint8_t command = protocol_recv_buffer[0];

    switch (command) {

        case COMMAND_ADC_0:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put(temperature_0);

        break;

        case COMMAND_ADC_1:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put(temperature_1);

        break;

        case COMMAND_GET_RPM_0:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put((uint8_t) (rpm_0 >> 8));
            protocol_send_buffer_put((uint8_t) rpm_0);

        break;

        case COMMAND_GET_RPM_1:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put((uint8_t) (rpm_1 >> 8));
            protocol_send_buffer_put((uint8_t) rpm_1);

        break;

        case COMMAND_GET_RPM_2:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put((uint8_t) (rpm_2 >> 8));
            protocol_send_buffer_put((uint8_t) rpm_2);

        break;

        case COMMAND_GET_RPM_3:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put((uint8_t) (rpm_3 >> 8));
            protocol_send_buffer_put((uint8_t) rpm_3);

        break;

        case COMMAND_SET_PWM_0:

            fan_set_pwm(0, protocol_recv_buffer[1]);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_SET_PWM_1:

            fan_set_pwm(1, protocol_recv_buffer[1]);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_SET_PWM_2:

            fan_set_pwm(2, protocol_recv_buffer[1]);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_SET_PWM_3:

            fan_set_pwm(3, protocol_recv_buffer[1]);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_ENABLE_0:

            fan_enable(0);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_ENABLE_1:

            fan_enable(1);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_ENABLE_2:

            fan_enable(2);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_ENABLE_3:

            fan_enable(3);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_0:

            fan_disable(0);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_1:

            fan_disable(1);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_2:

            fan_disable(2);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_3:

            fan_disable(3);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_ECHO:

            for (uint8_t i = 0; i < protocol_recv_buffer_length - 1; i++) {

                protocol_send_buffer_put(protocol_recv_buffer[i]);
            }

        break;
    }
}

// Executes the given command.

void protocol_command() {

    // Decodes USART input into our own
    // receive buffer.

    hex_decode(
        usart_buffer_recv_data,
        protocol_recv_buffer,
        usart_buffer_recv_length);

    // Set the receive buffer length.

    protocol_recv_buffer_length = usart_buffer_recv_length / 2;

    // Prepare buffer for sending.

    protocol_send_buffer_reset();

    // Verify checksum.

    if (protocol_verify()) {

        // Run command.

        protocol_command_run();

    } else {

        // Send back that checksum failed.

        protocol_send_buffer_put(RESPONSE_CHECKSUM_FAIL);
    }

    // Add crc.

    protocol_send_buffer_put_crc();

    // Encodes output data into output
    // USART buffer.

    hex_encode(
        protocol_send_buffer,
        usart_buffer_send_data,
        protocol_send_buffer_length);

    // Sets manually the output buffer length.

    usart_buffer_send_length = 2 * protocol_send_buffer_length;
}
