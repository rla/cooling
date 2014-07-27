var Buffer = require('buffer').Buffer;
var pearson = require('./pearson');

// Possible commands.

var commands = {

    TEMP_0: 1,
    TEMP_1: 2,

    GET_RPM_0: 3,
    GET_RPM_1: 4,
    GET_RPM_2: 5,
    GET_RPM_3: 6,

    SET_PWM_0: 7,
    SET_PWM_1: 8,
    SET_PWM_2: 9,
    SET_PWM_3: 10,

    GET_PWM_0: 11,
    GET_PWM_1: 12,
    GET_PWM_2: 13,
    GET_PWM_3: 14,

    ENABLE_0: 15,
    ENABLE_1: 16,
    ENABLE_2: 17,
    ENABLE_3: 18,

    DISABLE_0: 19,
    DISABLE_1: 20,
    DISABLE_2: 21,
    DISABLE_3: 22,

    ECHO: 254
};

exports.temp0 = function() {

    return singleByteCommand(commands.TEMP_0);
};

exports.temp1 = function() {

    return singleByteCommand(commands.TEMP_1);
};

exports.echo = function(byte) {

    var buffer = new Buffer(3);

    buffer.writeUInt8(commands.ECHO, 0);
    buffer.writeUInt8(byte, 1);
    buffer.writeUInt8(pearson(buffer, 0, 2), 2);

    return buffer.toString('hex');
};

exports.setPwm0 = function(pwm) {

    return singleArgCommand(commands.SET_PWM_0, pwm);
};

exports.setPwm1 = function(pwm) {

    return singleArgCommand(commands.SET_PWM_1, pwm);
};

exports.setPwm2 = function(pwm) {

    return singleArgCommand(commands.SET_PWM_2, pwm);
};

exports.setPwm3 = function(pwm) {

    return singleArgCommand(commands.SET_PWM_3, pwm);
};

exports.rpm0 = function() {

    return singleByteCommand(commands.GET_RPM_0);
};

exports.rpm1 = function() {

    return singleByteCommand(commands.GET_RPM_1);
};

exports.rpm2 = function() {

    return singleByteCommand(commands.GET_RPM_2);
};

exports.rpm3 = function() {

    return singleByteCommand(commands.GET_RPM_3);
};

exports.disable0 = function() {

    return singleByteCommand(commands.DISABLE_0);
};

exports.disable1 = function() {

    return singleByteCommand(commands.DISABLE_1);
};

exports.disable2 = function() {

    return singleByteCommand(commands.DISABLE_2);
};

exports.disable3 = function() {

    return singleByteCommand(commands.DISABLE_3);
};

exports.enable0 = function() {

    return singleByteCommand(commands.ENABLE_0);
};

exports.enable1 = function() {

    return singleByteCommand(commands.ENABLE_1);
};

exports.enable2 = function() {

    return singleByteCommand(commands.ENABLE_2);
};

exports.enable3 = function() {

    return singleByteCommand(commands.ENABLE_3);
};

// Produces hex string for single-byte command.
// All commands without arguments are single-byte
// commands.

function singleByteCommand(command) {

    var buffer = new Buffer(2);

    buffer.writeUInt8(command, 0);
    buffer.writeUInt8(pearson(buffer, 0, 1), 1);

    return buffer.toString('hex');
}

function singleArgCommand(command, arg) {

    var buffer = new Buffer(3);

    buffer.writeUInt8(command, 0);
    buffer.writeUInt8(arg, 1);
    buffer.writeUInt8(pearson(buffer, 0, 2), 2);

    return buffer.toString('hex');
}
