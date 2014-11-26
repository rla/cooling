var Buffer = require('buffer').Buffer;
var pearson = require('./pearson');

// Possible response types.

var responses = {

    OK: 255,
    FAIL: 254,
    CHECKSUM_FAIL: 253
};

// Decoder for responses
// without arguments.

exports.noValueDecoder = function(line, cb) {

    decode(line, function(err, buffer) {

        if (err) {

            cb(err);

        } else {

            if (buffer.length !== 2) {

                cb(new Error('Invalid response length for no-argument response, line: ' + line));

            } else {

                cb(null);
            }
        }
    });
};

// Decoder for single-byte unsigned
// integer.

exports.byteDecoder = function(line, cb) {

    decode(line, function(err, buffer) {

        if (err) {

            cb(err);

        } else {

            // [response_type, byte value, checksum]

            if (buffer.length !== 3) {

                cb(new Error('Invalid response length for byte, line: ' + line));

            } else {

                cb(null, buffer.readUInt8(1));
            }
        }
    });
};

// Returns decoder function for
// two-byte integers.

exports.shortDecoder = function(line, cb) {

    decode(line, function(err, buffer) {

        if (err) {

            cb(err);

        } else {

            // [response_type, byte1 value, byte2 value, checksum]

            if (buffer.length !== 4) {

                cb(new Error('Invalid response length for short, line: ' + line));

            } else {

                cb(null, buffer.readUInt16BE(1));
            }
        }
    });
};

// Control line bits.
// FIXME duplicated code

var controlBits = {

    ENABLED: 0,
    AFFECT_FAN0: 1,
    AFFECT_FAN1: 2,
    AFFECT_FAN2: 3,
    AFFECT_FAN3: 4
};

// Decodes a temperature control line.

exports.lineDecoder = function(line, cb) {

    decode(line, function(err, buffer) {

        if (err) {

            cb(err);

        } else {

            // [ response_type, control, min_temp, max_temp,
            //  fan0_pwm, fan1_pwm, fan2_pwm, fan3_pwm, checksum ]

            var control = buffer.readUInt8(1);

            var data = {

                enabled: !!(control & (1 << controlBits.ENABLED)),

                affect_fan0: !!(control & (1 << controlBits.AFFECT_FAN0)),

                affect_fan1: !!(control & (1 << controlBits.AFFECT_FAN1)),

                affect_fan2: !!(control & (1 << controlBits.AFFECT_FAN2)),

                affect_fan3: !!(control & (1 << controlBits.AFFECT_FAN3)),

                min_temp: buffer.readUInt8(2),

                max_temp: buffer.readUInt8(3),

                fan0_pwm: buffer.readUInt8(4),

                fan1_pwm: buffer.readUInt8(5),

                fan2_pwm: buffer.readUInt8(6),

                fan3_pwm: buffer.readUInt8(7)
            };

            if (buffer.length !== 9) {

                cb(new Error('Invalid response length for short, line: ' + line));

            } else {

                cb(null, data);
            }
        }
    });
};

// Decodes hex-encoded response.
// Checks that buffer contains
// a valid response.

function decode(line, cb) {

    if (line.length < 2) {

        cb(new Error('Invalid response line: ' + line));

    } else {

        var buffer = new Buffer(line, 'hex');

        var type = buffer.readUInt8(0);

        if (type === responses.FAIL) {

            cb(new Error('Command failed'));

        } else if (type === responses.CHECKSUM_FAIL) {

            cb(new Error('Invalid command checksum'));

        } else if (type === responses.OK) {

            var checksum = pearson(buffer, 0, buffer.length - 1);

            if (checksum === buffer.readUInt8(buffer.length - 1)) {

                cb(null, buffer);

            } else {

                cb(new Error('Invalid response checksum, line: ' + line));
            }

        } else {

            cb(new Error('Invalid response type: ' + type));
        }
    }
}
