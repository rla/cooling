typedef struct {
    volatile uint8_t pin_rpm;
    volatile uint8_t pin_enable;
    volatile uint8_t *port_pwm;
    volatile uint16_t rpm;
} fan_t;

volatile fan_t fans[4];

// Initializes fans data.

void init_fans_data() {

    fans[0].pin_rpm = PC2;
    fans[0].pin_enable = PB0;
    fans[0].port_pwm = &OCR0A;
    fans[0].rpm = 0;

    fans[1].pin_rpm = PC3;
    fans[1].pin_enable = PB1;
    fans[1].port_pwm = &OCR0B;
    fans[1].rpm = 0;

    fans[2].pin_rpm = PC4;
    fans[2].pin_enable = PB2;
    fans[2].port_pwm = &OCR2A;
    fans[2].rpm = 0;

    fans[3].pin_rpm = PC5;
    fans[3].pin_enable = PB4;
    fans[3].port_pwm = &OCR2B;
    fans[3].rpm = 0;
}

// Sets given fan PWM.

void fan_set_pwm(uint8_t fan, uint8_t pwm) {

    (*fans[fan].port_pwm) = pwm;
}

// Enables the given fan.

void fan_enable(uint8_t fan) {

    uint8_t pin = fans[fan].pin_enable;

    PORTB |= (1 << pin);
}

// Disables the given fan.

void fan_disable(uint8_t fan) {

    fan_set_pwm(fan, 0);

    uint8_t pin = fans[fan].pin_enable;

    PORTB &= ~(1 << pin);
}
