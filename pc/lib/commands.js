var decode = require('./decode');
var encode = require('./encode');

module.exports = {

    TEMP_0: {

        id: 1,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'Query sensor 0 temperature.'
    },

    TEMP_1: {

        id: 2,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'Query sensor 1 temperature.'
    },

    GET_RPM_0: {

        id: 3,
        encode: encode.nullary,
        decode: decode.short,
        description: 'Query fan 0 RPM.'
    },

    GET_RPM_1: {

        id: 4,
        encode: encode.nullary,
        decode: decode.short,
        description: 'Query fan 1 RPM.'
    },

    GET_RPM_2: {

        id: 5,
        encode: encode.nullary,
        decode: decode.short,
        description: 'Query fan 2 RPM.'
    },

    GET_RPM_3: {

        id: 6,
        encode: encode.nullary,
        decode: decode.short,
        description: 'Query fan 3 RPM.'
    },

    SET_PWM_0: {

        id: 7,
        encode: encode.byte,
        decode: decode.empty,
        description: 'Set fan 0 PWM (0-255).'
    },

    SET_PWM_1: {

        id: 8,
        encode: encode.byte,
        decode: decode.empty,
        description: 'Set fan 1 PWM (0-255).'
    },

    SET_PWM_2: {

        id: 9,
        encode: encode.byte,
        decode: decode.empty,
        description: 'Set fan 2 PWM (0-255)'
    },

    SET_PWM_3: {

        id: 10,
        encode: encode.byte,
        decode: decode.empty,
        description: 'Set fan 3 PWM (0-255)'
    },

    GET_PWM_0: {

        id: 11,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'Query fan 0 PWM level (0-255).'
    },

    GET_PWM_1: {

        id: 12,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'Query fan 1 PWM level (0-255).'
    },

    GET_PWM_2: {

        id: 13,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'Query fan 2 PWM level (0-255).'
    },

    GET_PWM_3: {

        id: 14,
        encode: encode.nullary,
        decode: decode.byte,
        description: 'Query fan 3 PWM level (0-255).'
    },

    ENABLE_0: {

        id: 15,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable fan 0.'
    },

    ENABLE_1: {

        id: 16,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable fan 1.'
    },

    ENABLE_2: {

        id: 17,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable fan 2.'
    },

    ENABLE_3: {

        id: 18,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable fan 3.'
    },

    DISABLE_0: {

        id: 19,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable fan 0.'
    },

    DISABLE_1: {

        id: 20,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable fan 1.'
    },

    DISABLE_2: {

        id: 21,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable fan 2.'
    },

    DISABLE_3: {

        id: 22,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable fan 3.'
    },

    TEMP0_SET: {

        id: 23,
        encode: encode.control,
        decode: decode.empty,
        description: 'Set control table line (index 0-4) for sensor 0.'
    },

    TEMP1_SET: {

        id: 24,
        encode: encode.control,
        decode: decode.empty,
        description: 'Set control table line (index 0-4) for sensor 1.'
    },

    TEMP0_GET: {

        id: 25,
        encode: encode.byte,
        decode: decode.control,
        description: 'Get control table line (index 0-4) for sensor 0.'
    },

    TEMP1_GET: {

        id: 26,
        encode: encode.byte,
        decode: decode.control,
        description: 'Get control table line (index 0-4) for sensor 1.'
    },

    ECHO: {

        id: 254,
        encode: encode.byte,
        decode: decode.byte,
        description: 'Sends and receives the given byte.'
    },

    ENABLE_STRETCH_0: {

        id: 28,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable pulse stretch for fan 0.'
    },

    ENABLE_STRETCH_1: {

        id: 29,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable pulse stretch for fan 1.'
    },

    ENABLE_STRETCH_2: {

        id: 30,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable pulse stretch for fan 2.'
    },

    ENABLE_STRETCH_3: {

        id: 31,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Enable pulse stretch for fan 3.'
    },

    DISABLE_STRETCH_0: {

        id: 32,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable pulse stretch for fan 0.'
    },

    DISABLE_STRETCH_1: {

        id: 33,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable pulse stretch for fan 1.'
    },

    DISABLE_STRETCH_2: {

        id: 34,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable pulse stretch for fan 2.'
    },

    DISABLE_STRETCH_3: {

        id: 35,
        encode: encode.nullary,
        decode: decode.empty,
        description: 'Disable pulse stretch for fan 3.'
    },

    GET_STRETCH: {

        id: 27,
        encode: encode.nullary,
        decode: decode.stretch,
        description: 'Query pulse stretch settings.'
    }
};
