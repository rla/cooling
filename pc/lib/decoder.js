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
