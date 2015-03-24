var decode = require('./decode');
var encode = require('./encode');

module.exports = {

    TEMP0: {

        id: 1,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'query sensor 0 temperature'
    },

    TEMP1: {

        id: 2,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'query sensor 1 temperature'
    },

    RPM0: {

        id: 3,
        encode: encode.nullary,
        decode: decode.short,
        description: 'query fan 0 RPM'
    },

    RPM1: {

        id: 4,
        encode: encode.nullary,
        decode: decode.short,
        description: 'query fan 1 RPM'
    },

    RPM2: {

        id: 5,
        encode: encode.nullary,
        decode: decode.short,
        description: 'query fan 2 RPM'
    },

    RPM3: {

        id: 6,
        encode: encode.nullary,
        decode: decode.short,
        description: 'query fan 3 RPM'
    },

    PWM0_SET: {

        id: 7,
        encode: encode.byte,
        decode: decode.empty,
        description: 'set fan 0 PWM (0-255)'
    },

    PWM1_SET: {

        id: 8,
        encode: encode.byte,
        decode: decode.empty,
        description: 'set fan 1 PWM (0-255)'
    },

    PWM2_SET: {

        id: 9,
        encode: encode.byte,
        decode: decode.empty,
        description: 'set fan 2 PWM (0-255)'
    },

    PWM3_SET: {

        id: 10,
        encode: encode.byte,
        decode: decode.empty,
        description: 'set fan 3 PWM (0-255)'
    },

    PWM0_GET: {

        id: 11,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'query fan 0 PWM level (0-255)'
    },

    PWM1_GET: {

        id: 12,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'query fan 1 PWM level (0-255)'
    },

    PWM2_GET: {

        id: 13,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'query fan 2 PWM level (0-255)'
    },

    PWM3_GET: {

        id: 14,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'query fan 3 PWM level (0-255)'
    },

    ENABLE0: {

        id: 15,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable fan 0'
    },

    ENABLE1: {

        id: 16,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable fan 1'
    },

    ENABLE2: {

        id: 17,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable fan 2'
    },

    ENABLE3: {

        id: 18,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable fan 3'
    },

    DISABLE0: {

        id: 19,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable fan 0'
    },

    DISABLE1: {

        id: 20,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable fan 1'
    },

    DISABLE2: {

        id: 21,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable fan 2'
    },

    DISABLE3: {

        id: 22,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable fan 3'
    },

    TEMP0_LINE_SET: {

        id: 23,
        encode: encode.control,
        decode: decode.empty,
        description: 'set control table line (0-4) for sensor 0'
    },

    TEMP1_LINE_SET: {

        id: 24,
        encode: encode.control,
        decode: decode.empty,
        description: 'set control table line (0-4) for sensor 1'
    },

    TEMP0_LINE_GET: {

        id: 25,
        encode: encode.byte,
        decode: decode.control,
        description: 'get control table line (0-4) for sensor 0'
    },

    TEMP1_LINE_GET: {

        id: 26,
        encode: encode.byte,
        decode: decode.control,
        description: 'get control table line (0-4) for sensor 1'
    },

    ECHO: {

        id: 254,
        encode: encode.byte,
        decode: decode.byte,
        description: 'sends and receives the given byte'
    },

    STRETCH0: {

        id: 28,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable pulse stretch for fan 0'
    },

    STRETCH1: {

        id: 29,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable pulse stretch for fan 1'
    },

    STRETCH2: {

        id: 30,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable pulse stretch for fan 2'
    },

    STRETCH3: {

        id: 31,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'enable pulse stretch for fan 3'
    },

    NOSTRETCH0: {

        id: 32,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable pulse stretch for fan 0'
    },

    NOSTRETCH1: {

        id: 33,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable pulse stretch for fan 1'
    },

    NOSTRETCH2: {

        id: 34,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable pulse stretch for fan 2'
    },

    NOSTRETCH3: {

        id: 35,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'disable pulse stretch for fan 3'
    },

    STRETCH_INFO: {

        id: 27,
        encode: encode.nullary,
        decode: decode.stretch,
        description: 'query pulse stretch settings'
    }
};
