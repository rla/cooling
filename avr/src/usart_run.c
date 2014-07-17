// USART send/receive logics.

ISR(USART_RX_vect) {

    uint8_t recv = UDR0;

    // Only execute command when
    // data from old commands has been
    // fully sent.

    if (usart_buffer_sending()) {

        return;
    }

    // messages are newline-terminated.

    if (recv == '\n') {

        // Decode and run command.

        protocol_command();

        // Reset receive buffer.

        usart_buffer_recv_reset();

        // Send data.

        usart_buffer_send_start();

    } else {

        // Accumulate data.

        usart_buffer_recv_put(recv);
    }
}

ISR(USART_TX_vect) {

    // When byte is sent, try send more.

    usart_buffer_send();
}
