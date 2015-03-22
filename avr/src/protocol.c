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

#define COMMAND_TEMP0_SET 23
#define COMMAND_TEMP1_SET 24

#define COMMAND_TEMP0_GET 25
#define COMMAND_TEMP1_GET 26

#define COMMAND_GET_STRETCH 27

#define COMMAND_STRETCH_ENABLE_0 28
#define COMMAND_STRETCH_ENABLE_1 29
#define COMMAND_STRETCH_ENABLE_2 30
#define COMMAND_STRETCH_ENABLE_3 31

#define COMMAND_STRETCH_DISABLE_0 32
#define COMMAND_STRETCH_DISABLE_1 33
#define COMMAND_STRETCH_DISABLE_2 34
#define COMMAND_STRETCH_DISABLE_3 35

#define COMMAND_ECHO 254

#define RESPONSE_OK 255
#define RESPONSE_FAIL 254
#define RESPONSE_CHECKSUM_FAIL 253

// Must be <= USART_BUFFER_SIZE

#define PROTOCOL_BUFFER_SIZE 20

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

// Reads the control line from
// the receive buffer.
// This must be consistent with the
// t_temp_line definition.

void protocol_read_control_line(t_temp_line *line) {

    line->control = protocol_recv_buffer[2];
    line->min_temp = protocol_recv_buffer[3];
    line->max_temp = protocol_recv_buffer[4];
    line->fan0_pwm = protocol_recv_buffer[5];
    line->fan1_pwm = protocol_recv_buffer[6];
    line->fan2_pwm = protocol_recv_buffer[7];
    line->fan3_pwm = protocol_recv_buffer[8];
}

// Puts the control line data into
// the send buffer.

void protocol_put_control_line(t_temp_line *line) {

    protocol_send_buffer_put(line->control);
    protocol_send_buffer_put(line->min_temp);
    protocol_send_buffer_put(line->max_temp);
    protocol_send_buffer_put(line->fan0_pwm);
    protocol_send_buffer_put(line->fan1_pwm);
    protocol_send_buffer_put(line->fan2_pwm);
    protocol_send_buffer_put(line->fan3_pwm);
}

// Sets a control line for temperature 0.

uint8_t protocol_command_run_set_temp0() {

    t_temp_line line;

    // Line index.

    uint8_t i = protocol_recv_buffer[1];

    if (i >= 5) {

        return 0;
    }

    protocol_read_control_line(&line);

    adjust_write_temp0_line(i, &line);

    return 1;
}

// Sets a control line for temperature 1.

uint8_t protocol_command_run_set_temp1() {

    t_temp_line line;

    // Line index.

    uint8_t i = protocol_recv_buffer[1];

    if (i >= 5) {

        return 0;
    }

    protocol_read_control_line(&line);

    adjust_write_temp1_line(i, &line);

    return 1;
}

// Reads and saves a sensor 0 control line.

void protocol_command_run_get_temp0() {

    t_temp_line line;

    uint8_t i = protocol_recv_buffer[1];

    if (i >= 5) {

        protocol_send_buffer_put(RESPONSE_FAIL);

        return;
    }

    adjust_read_temp0_line(i, &line);

    protocol_send_buffer_put(RESPONSE_OK);

    protocol_put_control_line(&line);
}

// Reads and saves a sensor 0 control line.

void protocol_command_run_get_temp1() {

    t_temp_line line;

    uint8_t i = protocol_recv_buffer[1];

    if (i >= 5) {

        protocol_send_buffer_put(RESPONSE_FAIL);

        return;
    }

    adjust_read_temp1_line(i, &line);

    protocol_send_buffer_put(RESPONSE_OK);

    protocol_put_control_line(&line);
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

            fan_set_pwm(0, 0);
            fan_disable(0);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_1:

            fan_set_pwm(1, 0);
            fan_disable(1);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_2:

            fan_set_pwm(2, 0);
            fan_disable(2);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_DISABLE_3:

            fan_set_pwm(3, 0);
            fan_disable(3);
            protocol_send_buffer_put(RESPONSE_OK);

        break;

        case COMMAND_TEMP0_SET:

            if (protocol_command_run_set_temp0()) {

                protocol_send_buffer_put(RESPONSE_OK);

            } else {

                protocol_send_buffer_put(RESPONSE_FAIL);
            }

        break;

        case COMMAND_TEMP1_SET:

            if (protocol_command_run_set_temp1()) {

                protocol_send_buffer_put(RESPONSE_OK);

            } else {

                protocol_send_buffer_put(RESPONSE_FAIL);
            }

        break;

        case COMMAND_TEMP0_GET:

            protocol_command_run_get_temp0();

        break;

        case COMMAND_TEMP1_GET:

            protocol_command_run_get_temp1();

        break;

        case COMMAND_GET_STRETCH:

            protocol_send_buffer_put(RESPONSE_OK);

            uint8_t stretch[4];

            fan_stretch_read_info(stretch);

            for (uint8_t i = 0; i < 4; i++) {

                protocol_send_buffer_put(stretch[i]);
            }

        break;

        case COMMAND_STRETCH_ENABLE_0:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_enable(0);

        break;

        case COMMAND_STRETCH_ENABLE_1:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_enable(1);

        break;

        case COMMAND_STRETCH_ENABLE_2:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_enable(2);

        break;

        case COMMAND_STRETCH_ENABLE_3:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_enable(3);

        break;

        case COMMAND_STRETCH_DISABLE_0:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_disable(0);

        break;

        case COMMAND_STRETCH_DISABLE_1:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_disable(1);

        break;

        case COMMAND_STRETCH_DISABLE_2:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_disable(2);

        break;

        case COMMAND_STRETCH_DISABLE_3:

            protocol_send_buffer_put(RESPONSE_OK);

            fan_stretch_disable(3);

        break;

        case COMMAND_ECHO:

            protocol_send_buffer_put(RESPONSE_OK);
            protocol_send_buffer_put(protocol_recv_buffer[1]);

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
