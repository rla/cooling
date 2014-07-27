var connection = require('./connection');
var command = require('./command');

exports.open = function(file, cb) {

    var con = connection.open(file, cb);

    var device = {};

    // Device's sensor 0 temperature.

    device.temp0 = function(cb) {

        con.send(command.temp0(), cb);
    };

    // Device's sensor 1 temperature.

    device.temp1 = function(cb) {

        con.send(command.temp1(), cb);
    };

    // Queries fan 0 RPM.

    device.rpm0 = function(cb) {

        con.send(command.rpm0(), cb);
    };

    // Queries fan 1 RPM.

    device.rpm1 = function(cb) {

        con.send(command.rpm1(), cb);
    };

    // Queries fan 2 RPM.

    device.rpm2 = function(cb) {

        con.send(command.rpm2(), cb);
    };

    // Queries fan 3 RPM.

    device.rpm3 = function(cb) {

        con.send(command.rpm3(), cb);
    };

    // Enables fan 0.

    device.enable0 = function(cb) {

        con.send(command.enable0(), cb);
    };

    // Enables fan 1.

    device.enable1 = function(cb) {

        con.send(command.enable1(), cb);
    };

    // Enables fan 2.

    device.enable2 = function(cb) {

        con.send(command.enable2(), cb);
    };

    // Enables fan 3.

    device.enable3 = function(cb) {

        con.send(command.enable3(), cb);
    };

    // Disables fan 0.

    device.disable0 = function(cb) {

        con.send(command.disable0(), cb);
    };

    // Disables fan 1.

    device.disable1 = function(cb) {

        con.send(command.disable1(), cb);
    };

    // Disables fan 2.

    device.disable2 = function(cb) {

        con.send(command.disable2(), cb);
    };

    // Disables fan 3.

    device.disable3 = function(cb) {

        con.send(command.disable3(), cb);
    };

    // Sets PWM for fan 0.

    device.setPwm0 = function(pwm, cb) {

        con.send(command.setPwm0(pwm), cb);
    };

    // Sets PWM for fan 1.

    device.setPwm1 = function(pwm, cb) {

        con.send(command.setPwm1(pwm), cb);
    };

    // Sets PWM for fan 2.

    device.setPwm2 = function(pwm, cb) {

        con.send(command.setPwm2(pwm), cb);
    };

    // Sets PWM for fan 3.

    device.setPwm3 = function(pwm, cb) {

        con.send(command.setPwm3(pwm), cb);
    };

    // Closes the underlying connection.

    device.close = function(cb) {

        con.close(cb);
    };

    // Flushes underlying port.

    device.flush = function(cb) {

        con.flush(cb);
    };

    return device;
};
