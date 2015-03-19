var pearson = require('./pearson');

// Decodes hex-encoded response.
// Checks that buffer contains
// a valid response.
// length - expected decoded buffer length.

module.exports = function(line, length) {

    if (line.length < 2) {

        throw new Error('Invalid response line.');

    } else {

        var buffer = new Buffer(line, 'hex');

        var type = buffer.readUInt8(0);

        if (type === responses.FAIL) {

            throw new Error('Command failed.');

        } else if (type === responses.CHECKSUM_FAIL) {

            throw new Error('Invalid command checksum.');

        } else if (type === responses.OK) {

            var checksum = pearson(buffer, 0, buffer.length - 1);

            if (checksum === buffer.readUInt8(buffer.length - 1)) {

                if (buffer.length !== length) {

                    throw new Error('Invalid response length, expected ' + length + '.');

                } else {

                    return buffer;
                }

            } else {

                throw new Error('Invalid response checksum.');
            }

        } else {

            throw new Error('Invalid response type ' + type + '.');
        }
    }
};

// Possible response types.

var responses = {

    OK: 255,
    FAIL: 254,
    CHECKSUM_FAIL: 253
};
