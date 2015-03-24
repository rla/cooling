var commands = require('./commands');

module.exports = function() {

    var list = Object.keys(commands).sort();

    console.log('Usage: rcooling-query --port <port> --command <command> [arguments]');
    console.log('Recognized commands: ');

    list.forEach(function(name) {

        var command = commands[name];

        if (command.description) {

            console.log('  ' + pad(name.toLowerCase(), 14) + ' ' + command.description);
        }
    });
};

// Pads the given string to
// reach the given length.

function pad(string, length) {

    var count = length - string.length;

    if (count > 0) {

        return string + Array(count + 1).join(' ');
    }

    return string;
}
