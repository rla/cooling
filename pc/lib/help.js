var commands = require('./commands');

module.exports = function() {

    var list = Object.keys(commands).sort();

    console.log('Usage: rcooling-query --port <port> --command <command> [arguments]');
    console.log('Recognized commands: ');

    list.forEach(function(name) {

        var command = commands[name];

        if (command.description) {

            console.log('  ' + name.toLowerCase() + ' - ' + command.description);
        }
    });
};
