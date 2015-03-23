var Promise = require('bluebird');
var decode_line = require('./decode_line');
var control_bits = require('./control').control_bits;

// Decoder for responses
// without arguments.

exports.empty = function(line) {

    // [response_type, checksum]

    decode_line(line, 2);

    return true;
};

// Decoder for single-byte
// unsigned integer.

exports.byte = function(line) {

    // [response_type, byte value, checksum]

    return decode_line(line, 3).readUInt8(1);
};

// Decoder function for
// two-byte BE integers.

exports.short = function(line) {

    // [response_type, byte1 value, byte2 value, checksum]

    return decode_line(line, 4).readUInt16BE(1);
};

// Decoder for control line data.

exports.control = function(line) {

    // [ response_type, control, min_temp, max_temp,
    //  fan0_pwm, fan1_pwm, fan2_pwm, fan3_pwm, checksum ]

    var buffer = decode_line(line, 9);

    var control = buffer.readUInt8(1);

    return {

        enabled: !!(control & (1 << control_bits.ENABLED)),

        affect_fan1: !!(control & (1 << control_bits.AFFECT_FAN1)),

        affect_fan2: !!(control & (1 << control_bits.AFFECT_FAN2)),

        affect_fan3: !!(control & (1 << control_bits.AFFECT_FAN3)),

        affect_fan4: !!(control & (1 << control_bits.AFFECT_FAN4)),

        min_temp: buffer.readUInt8(2),

        max_temp: buffer.readUInt8(3),

        fan0_pwm: buffer.readUInt8(4),

        fan1_pwm: buffer.readUInt8(5),

        fan2_pwm: buffer.readUInt8(6),

        fan3_pwm: buffer.readUInt8(7)
    };
};

// Decoder for pulse stretch info.

exports.stretch = function(line) {

    // [response_type, fan0_stretch, fan1_stretch,
    //  fan2_stretch, fan3_stretch, checksum]

    var buffer = decode_line(line, 6);

    return {

        fan0: !!buffer.readUInt8(1),

        fan1: !!buffer.readUInt8(2),

        fan2: !!buffer.readUInt8(3),

        fan3: !!buffer.readUInt8(4)
    };
};
