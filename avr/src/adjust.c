// Available global variables.
//
// rpm_0, ..., rpm_3
// temperature_0, temperature_1
//
// Control functions

void adjust() {

    // Dividing zone 0 into 4 regions:

    // below 30C
    // 30-34C
    // 35-38C
    // alove 38C

    if (temperature_0 < 30) {

        // Both fans are off.

        fan_disable(0);
        fan_disable(1);

    } else if (temperature_0 < 35) {

        // Fan 0 at half power

        fan_enable(0);
        fan_set_pwm(0, 128);

        // Fan 1 off

        fan_disable(1);

    } else if (temperature_0 < 39) {

        // Both fans at half power.

        fan_enable(0);
        fan_enable(1);

        fan_set_pwm(0, 128);
        fan_set_pwm(1, 128);

    } else {

        // Both fans at full power.

        fan_enable(0);
        fan_enable(1);

        fan_set_pwm(0, 255);
        fan_set_pwm(1, 255);
    }
}
