// Sets the error output.

void set_error() {

    PORTD |= (1 << PD2);
}

void check_error() {

    if (fan_enabled(0) && rpm_0 == 0) {

        // Fan 0 has stopped.

        set_error();
    }

    if (fan_enabled(1) && rpm_1 == 0) {

        // Fan 1 has stopped.

        set_error();
    }

    if (fan_enabled(2) && rpm_2 == 0) {

        // Fan 2 has stopped.

        set_error();
    }

    if (fan_enabled(3) && rpm_3 == 0) {

        // Fan 3 has stopped.

        set_error();
    }
}
