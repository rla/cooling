var Buffer = require('buffer').Buffer;
var pearson = require('./pearson');

var commands = {

    COMMAND_ADC_0: 1,
    COMMAND_ADC_1: 2,

    COMMAND_GET_RPM_0: 3,
    COMMAND_GET_RPM_1: 4,
    COMMAND_GET_RPM_2: 5,
    COMMAND_GET_RPM_3: 6,

    COMMAND_SET_PWM_0: 7,
    COMMAND_SET_PWM_1: 8,
    COMMAND_SET_PWM_2: 9,
    COMMAND_SET_PWM_3: 10,

    COMMAND_GET_PWM_0: 11,
    COMMAND_GET_PWM_1: 12,
    COMMAND_GET_PWM_2: 13,
    COMMAND_GET_PWM_3: 14,

    COMMAND_ENABLE_0: 15,
    COMMAND_ENABLE_1: 16,
    COMMAND_ENABLE_2: 17,
    COMMAND_ENABLE_3: 18,

    COMMAND_DISABLE_0: 19,
    COMMAND_DISABLE_1: 20,
    COMMAND_DISABLE_2: 21,
    COMMAND_DISABLE_3: 22,

    COMMAND_ECHO: 254,

    COMMAND_END: 0,
    COMMAND_OK: 255
};

exports.echo = function(byte) {

    var buffer = new Buffer(3);

    buffer.writeUInt8(commands.COMMAND_ECHO, 0);
    buffer.writeUInt8(byte, 1);
    buffer.writeUInt8(pearson(buffer, 0, 2), 2);

    return buffer.toString('hex');
};
