var encoder = require('./encoder');
var decoder = require('./decoder');

// FIXME encode message right away.

// Retrieves temperature from sensor 0.

exports.temp0 = function() {

    return { encoder: encoder.temp0, decoder: decoder.byteDecoder };
};

// Retrieves temperature from sensor 1.

exports.temp1 = function() {

    return { encoder: encoder.temp1, decoder: decoder.byteDecoder };
};

// Sets a control line for temperature 0.

exports.setTemp0Control = function(index, data) {

    return { encoder: encoder.setTemp0Control.bind(null, index, data),
        decoder: decoder.noValueDecoder };
};

// Sets a control line for temperature 1.

exports.setTemp1Control = function(index, data) {

    return { encoder: encoder.setTemp1Control.bind(null, index, data),
        decoder: decoder.noValueDecoder };
};

// Gets a control line for temperature 0.

exports.getTemp0Control = function(index) {

    return { encoder: encoder.getTemp0Control.bind(null, index),
        decoder: decoder.lineDecoder };
};

// Gets a control line for temperature 1.

exports.getTemp1Control = function(index) {

    return { encoder: encoder.getTemp1Control.bind(null, index),
        decoder: decoder.lineDecoder };
};

// Retrieves RPM of fan 0.

exports.rpm0 = function() {

    return { encoder: encoder.rpm0, decoder: decoder.shortDecoder };
};

// Retrieves RPM of fan 1.

exports.rpm1 = function() {

    return { encoder: encoder.rpm1, decoder: decoder.shortDecoder };
};

// Retrieves RPM of fan 2.

exports.rpm2 = function() {

    return { encoder: encoder.rpm2, decoder: decoder.shortDecoder };
};

// Retrieves RPM of fan 3.

exports.rpm3 = function() {

    return { encoder: encoder.rpm3, decoder: decoder.shortDecoder };
};

// Enables fan 0.

exports.enable0 = function() {

    return { encoder: encoder.enable0, decoder: decoder.noValueDecoder };
};

// Enables fan 1.

exports.enable1 = function() {

    return { encoder: encoder.enable1, decoder: decoder.noValueDecoder };
};

// Enables fan 2.

exports.enable2 = function() {

    return { encoder: encoder.enable2, decoder: decoder.noValueDecoder };
};

// Enables fan 3.

exports.enable3 = function() {

    return { encoder: encoder.enable3, decoder: decoder.noValueDecoder };
};

// Disables fan 0.

exports.disable0 = function() {

    return { encoder: encoder.disable0, decoder: decoder.noValueDecoder };
};

// Disables fan 1.

exports.disable1 = function() {

    return { encoder: encoder.disable1, decoder: decoder.noValueDecoder };
};

// Disables fan 2.

exports.disable2 = function() {

    return { encoder: encoder.disable2, decoder: decoder.noValueDecoder };
};

// Disables fan 3.

exports.disable3 = function() {

    return { encoder: encoder.disable3, decoder: decoder.noValueDecoder };
};

// Sets fan 0 PWM.

exports.setPwm0 = function(pwm) {

    return { encoder: encoder.setPwm0.bind(null, pwm), decoder: decoder.noValueDecoder };
};

// Sets fan 1 PWM.

exports.setPwm1 = function(pwm) {

    return { encoder: encoder.setPwm1.bind(null, pwm), decoder: decoder.noValueDecoder };
};

// Sets fan 2 PWM.

exports.setPwm2 = function(pwm) {

    return { encoder: encoder.setPwm2.bind(null, pwm), decoder: decoder.noValueDecoder };
};

// Sets fan 3 PWM.

exports.setPwm3 = function(pwm) {

    return { encoder: encoder.setPwm3.bind(null, pwm), decoder: decoder.noValueDecoder };
};
