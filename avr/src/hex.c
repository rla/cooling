// Decodes single hex character.

uint8_t hex_decode_single(uint8_t ch) {

    switch (ch) {

        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': return 10;
        case 'b': return 11;
        case 'c': return 12;
        case 'd': return 13;
        case 'e': return 14;
        case 'f': return 15;
    }

    return 0;
}

// Returns hex encoding of lower
// nibble of the given value.

uint8_t hex_encode_single(uint8_t value) {

    switch (value & 0x0F) {

        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'a';
        case 11: return 'b';
        case 12: return 'c';
        case 13: return 'd';
        case 14: return 'e';
        case 15: return 'f';
    }

    return '0';
}

// Decodes len hex characters from source.
// len must be an even number.

void hex_decode(volatile uint8_t *source, volatile uint8_t *dest, uint8_t len) {

    uint8_t bytes = len/2;

    for (uint8_t i = 0; i < bytes; i++) {

        uint8_t higher = hex_decode_single(source[i * 2]);
        uint8_t lower = hex_decode_single(source[i * 2 + 1]);

        dest[i] = (higher << 4) + lower;
    }
}

// Encodes len bytes from source to hex
// in the dest buffer.

void hex_encode(volatile uint8_t *source, volatile uint8_t *dest, uint8_t len) {

    for (uint8_t i = 0; i < len; i++) {

        dest[i * 2] = hex_encode_single(source[i] >> 4);
        dest[i * 2 + 1] = hex_encode_single(source[i]);
    }
}
