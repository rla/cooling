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

        fan1_pwm: buffer.readUInt8(4),

        fan2_pwm: buffer.readUInt8(5),

        fan3_pwm: buffer.readUInt8(6),

        fan4_pwm: buffer.readUInt8(7)
    };
};
