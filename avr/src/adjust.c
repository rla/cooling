#include <avr/eeprom.h>

#define ADJUST_CONTROL_ENABLED 0
#define ADJUST_CONTROL_AFFECT_FAN0 1
#define ADJUST_CONTROL_AFFECT_FAN1 2
#define ADJUST_CONTROL_AFFECT_FAN2 3
#define ADJUST_CONTROL_AFFECT_FAN3 4

// Available global variables.
//
// rpm_0, ..., rpm_3
// temperature_0, temperature_1
//
// Control functions

typedef struct {

    uint8_t control;
    uint8_t min_temp;
    uint8_t max_temp;
    uint8_t fan0_pwm;
    uint8_t fan1_pwm;
    uint8_t fan2_pwm;
    uint8_t fan3_pwm;

} t_temp_line;

t_temp_line EEMEM adjust_temp0_lines[5] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 }
};

t_temp_line EEMEM adjust_temp1_lines[5] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 }
};

void adjust_write_temp0_line(uint8_t i, t_temp_line *line) {

    eeprom_update_block(line, &adjust_temp0_lines[i], sizeof(t_temp_line));
}

void adjust_write_temp1_line(uint8_t i, t_temp_line *line) {

    eeprom_update_block(line, &adjust_temp1_lines[i], sizeof(t_temp_line));
}

void adjust_read_temp0_line(uint8_t i, t_temp_line *line) {

    eeprom_read_block(line, &adjust_temp0_lines[i], sizeof(t_temp_line));
}

void adjust_read_temp1_line(uint8_t i, t_temp_line *line) {

    eeprom_read_block(line, &adjust_temp1_lines[i], sizeof(t_temp_line));
}

// Checks that the given control line is activated.

uint8_t adjust_is_line_active(t_temp_line *line) {

    return line->control & (1 << ADJUST_CONTROL_ENABLED);
}

uint8_t adjust_line_affects_fan0(t_temp_line *line) {

    return line->control & (1 << ADJUST_CONTROL_AFFECT_FAN0);
}

uint8_t adjust_line_affects_fan1(t_temp_line *line) {

    return line->control & (1 << ADJUST_CONTROL_AFFECT_FAN1);
}

uint8_t adjust_line_affects_fan2(t_temp_line *line) {

    return line->control & (1 << ADJUST_CONTROL_AFFECT_FAN2);
}

uint8_t adjust_line_affects_fan3(t_temp_line *line) {

    return line->control & (1 << ADJUST_CONTROL_AFFECT_FAN3);
}

// Attempts to apply the given
// control line.

uint8_t adjust_try_apply_line(uint8_t temp, t_temp_line *line) {

    if (adjust_is_line_active(line)) {

        // Line is active.

        if (temp >= line->min_temp && temp <= line->max_temp) {

            // Matches temperature.

            if (adjust_line_affects_fan0(line)) {

                fan_set_pwm(0, line->fan0_pwm);

                if (line->fan0_pwm == 0) {

                    fan_disable(0);

                } else {

                    fan_enable(0);
                }
            }

            if (adjust_line_affects_fan1(line)) {

                fan_set_pwm(1, line->fan1_pwm);

                if (line->fan1_pwm == 0) {

                    fan_disable(1);

                } else {

                    fan_enable(1);
                }
            }

            if (adjust_line_affects_fan2(line)) {

                fan_set_pwm(2, line->fan2_pwm);

                if (line->fan2_pwm == 0) {

                    fan_disable(2);

                } else {

                    fan_enable(2);
                }
            }

            if (adjust_line_affects_fan3(line)) {

                fan_set_pwm(3, line->fan3_pwm);

                if (line->fan3_pwm == 0) {

                    fan_disable(3);

                } else {

                    fan_enable(3);
                }
            }

            return 1;
        }
    }

    return 0;
}

void adjust_temp0() {

    t_temp_line line;

    uint8_t i = 0;

    while (i < 5) {

        eeprom_read_block(&line, &adjust_temp0_lines[i], sizeof(t_temp_line));

        if (adjust_try_apply_line(temperature_0, &line)) {

            break;
        }

        i++;
    }
}

void adjust_temp1() {

    t_temp_line line;

    uint8_t i = 0;

    while (i < 5) {

        eeprom_read_block(&line, &adjust_temp1_lines[i], sizeof(t_temp_line));

        if (adjust_try_apply_line(temperature_1, &line)) {

            break;
        }

        i++;
    }
}

void adjust() {

    adjust_temp0();
    adjust_temp1();

    /*
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
    }*/
}
