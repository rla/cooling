var pearson = require('./pearson');
var control_bits = require('./control').control_bits;

// Encodes 0-ary (no-argument) command.

exports.nullary = function(command) {

    var buffer = new Buffer(2);

    buffer.writeUInt8(command, 0);
    buffer.writeUInt8(pearson(buffer, 0, 1), 1);

    return buffer.toString('hex');
};

// Encodes single byte argument command.

exports.byte = function(command, byte) {

    var buffer = new Buffer(3);

    buffer.writeUInt8(command, 0);
    buffer.writeUInt8(byte, 1);
    buffer.writeUInt8(pearson(buffer, 0, 2), 2);

    return buffer.toString('hex');
};

// Encodes control line command.

exports.control = function(command, index, data) {

    var buffer = new Buffer(10);

    buffer.writeUInt8(command, 0);
    buffer.writeUInt8(index, 1);

    writeControl(buffer, data);

    buffer.writeUInt8(pearson(buffer, 0, 9), 9);

    return buffer.toString('hex');
};

// Writes the control line data
// into the buffer.

function writeControl(buffer, data) {

    var control = 0, values = defaults(data);

    if (values.enabled) {

        control |= (1 << control_bits.ENABLED);
    }

    if (values.affect_fan0) {

        control |= (1 << control_bits.AFFECT_FAN1);
    }

    if (values.affect_fan1) {

        control |= (1 << control_bits.AFFECT_FAN2);
    }

    if (values.affect_fan2) {

        control |= (1 << control_bits.AFFECT_FAN3);
    }

    if (values.affect_fan3) {

        control |= (1 << control_bits.AFFECT_FAN4);
    }

    buffer.writeUInt8(control, 2);

    buffer.writeUInt8(values.min_temp, 3);
    buffer.writeUInt8(values.max_temp, 4);

    buffer.writeUInt8(values.fan0_pwm, 5);
    buffer.writeUInt8(values.fan1_pwm, 6);
    buffer.writeUInt8(values.fan2_pwm, 7);
    buffer.writeUInt8(values.fan3_pwm, 8);
}

// Extracts properties from
// data using defaults when missing.
// Returns new object.

function defaults(data) {

    // Default values.

    var values = {

        enabled: true,
        affect_fan0: false,
        affect_fan1: false,
        affect_fan2: false,
        affect_fan3: false,
        min_temp: 0,
        max_temp: 255,
        fan0_pwm: 255,
        fan1_pwm: 255,
        fan2_pwm: 255,
        fan3_pwm: 255
    };

    // Specialize with data:

    Object.keys(values).forEach(function(key) {

        if (typeof data[key] !== 'undefined') {

            values[key] = data[key];
        }
    });

    return values;
}
