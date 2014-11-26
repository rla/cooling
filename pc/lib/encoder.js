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

    TEMP0_SET: 23,
    TEMP1_SET: 24,

    TEMP0_GET: 25,
    TEMP1_GET: 26,

    ECHO: 254
};

// Control line bits.

var controlBits = {

    ENABLED: 0,
    AFFECT_FAN0: 1,
    AFFECT_FAN1: 2,
    AFFECT_FAN2: 3,
    AFFECT_FAN3: 4
};

exports.temp0 = function() {

    return singleByteCommand(commands.TEMP_0);
};

exports.temp1 = function() {

    return singleByteCommand(commands.TEMP_1);
};

// Retrieves control line for temperature 0.

exports.getTemp0Control = function(index) {

    return singleArgCommand(commands.TEMP0_GET, index);
};

// Retrieves control line for temperature 1.

exports.getTemp1Control = function(index) {

    return singleArgCommand(commands.TEMP1_GET, index);
};

// Sets control line for temperature 0.

exports.setTemp0Control = function(index, data) {

    var buffer = new Buffer(10);

    buffer.writeUInt8(commands.TEMP0_SET, 0);
    buffer.writeUInt8(index, 1);

    writeControl(buffer, data);

    buffer.writeUInt8(pearson(buffer, 0, 9), 9);

    return buffer.toString('hex');
};

// Sets control line for temperature 1.

exports.setTemp1Control = function(index, data) {

    var buffer = new Buffer(10);

    buffer.writeUInt8(commands.TEMP1_SET, 0);
    buffer.writeUInt8(index, 1);

    writeControl(buffer, data);

    buffer.writeUInt8(pearson(buffer, 0, 9), 9);

    return buffer.toString('hex');
};

function writeControl(buffer, data) {

    var control = 0;

    var enabled = propertyWithDefault('enabled', data, true);

    var affectFan0 = propertyWithDefault('affect_fan0', data, false);
    var affectFan1 = propertyWithDefault('affect_fan1', data, false);
    var affectFan2 = propertyWithDefault('affect_fan2', data, false);
    var affectFan3 = propertyWithDefault('affect_fan3', data, false);

    if (enabled) {

        control |= (1 << controlBits.ENABLED);
    }

    if (affectFan0) {

        control |= (1 << controlBits.AFFECT_FAN0);
    }

    if (affectFan1) {

        control |= (1 << controlBits.AFFECT_FAN1);
    }

    if (affectFan2) {

        control |= (1 << controlBits.AFFECT_FAN2);
    }

    if (affectFan3) {

        control |= (1 << controlBits.AFFECT_FAN3);
    }

    buffer.writeUInt8(control, 2);

    buffer.writeUInt8(propertyWithDefault('min_temp', data, 0), 3);
    buffer.writeUInt8(propertyWithDefault('max_temp', data, 255), 4);

    buffer.writeUInt8(propertyWithDefault('fan0_pwm', data, 255), 5);
    buffer.writeUInt8(propertyWithDefault('fan1_pwm', data, 255), 6);
    buffer.writeUInt8(propertyWithDefault('fan2_pwm', data, 255), 7);
    buffer.writeUInt8(propertyWithDefault('fan3_pwm', data, 255), 8);
}

// Reads given property. If not set, uses
// the default value.

function propertyWithDefault(key, obj, def) {

    if (typeof obj[key] === 'undefined') {

        return def;

    } else {

        return obj[key];
    }
}

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
