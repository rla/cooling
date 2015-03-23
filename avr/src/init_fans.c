// Disables all fans
// at startup.

void init_fans() {

    fan_disable(0);
    fan_disable(1);
    fan_disable(2);
    fan_disable(3);

    fan_set_pwm(0, 0);
    fan_set_pwm(1, 0);
    fan_set_pwm(2, 0);
    fan_set_pwm(3, 0);
}
