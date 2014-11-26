// Usart receive/send buffers.

#define USART_BUFFER_SIZE 40

volatile uint8_t usart_buffer_send_data[USART_BUFFER_SIZE];
volatile uint8_t usart_buffer_send_length = 0;
volatile uint8_t usart_buffer_send_pos = 0;
volatile uint8_t usart_buffer_send_terminated = 0;
volatile uint8_t usart_buffer_send_sent = 1;

volatile uint8_t usart_buffer_recv_data[USART_BUFFER_SIZE];
volatile uint8_t usart_buffer_recv_length = 0;

// Puts byte in the recv buffer.

void usart_buffer_recv_put(uint8_t byte) {

    if (usart_buffer_recv_length < USART_BUFFER_SIZE) {

        usart_buffer_recv_data[usart_buffer_recv_length] = byte;
        usart_buffer_recv_length += 1;
    }
}

// Resets the receive buffer.

void usart_buffer_recv_reset() {

    usart_buffer_recv_length = 0;
}

// True whether there is some data
// to be sent from previous command.

uint8_t usart_buffer_sending() {

    return !usart_buffer_send_sent;
}

// Sends one byte through USART.
// Sends until all bytes in the buffer
// have been sent.

void usart_buffer_send() {

    if (usart_buffer_send_sent) {

        // Current buffer is sent.

        return;
    }

    // Else terminate or send next byte.

    if (usart_buffer_send_terminated) {

        // Newline has been sent, reset.

        usart_buffer_send_length = 0;
        usart_buffer_send_pos = 0;
        usart_buffer_send_sent = 1;

    } else {

        if (usart_buffer_send_pos < usart_buffer_send_length) {

            // Some data in buffer to send.

            UDR0 = usart_buffer_send_data[usart_buffer_send_pos];
            usart_buffer_send_pos += 1;

        } else {

            // Terminate by sending newline.

            UDR0 = '\n';

            usart_buffer_send_terminated = 1;
        }
    }
}

// Starts the sending process.

void usart_buffer_send_start() {

    usart_buffer_send_sent = 0;
    usart_buffer_send_terminated = 0;

    // Send first byte or terminate.

    usart_buffer_send();
}
