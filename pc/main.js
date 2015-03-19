var args = require('./lib/args');
var help = require('./lib/help');
var encode = require('./lib/encode');
var commands = require('./lib/commands');
var connection = require('./lib/connection');

var options = args(process.argv);

if (options.help) {

    help();

    process.exit(0);

} else {

    if (!options.port || options.port.length === 0) {

        process.stderr.write('Port is not set. Try using --help.\n');
        process.exit(1);
    }

    if (!options.command || options.command.length === 0) {

        process.stderr.write('Command is not set. Try using --help.\n');
        process.exit(1);
    }

    var name = options.command[0];

    var command = commands[name.toUpperCase()];

    if (!command) {

        process.stderr.write('The given command ' + name.toLowerCase() +
            ' does not exist. Try using --help.\n');
        process.exit(1);
    }

    // Parsed command arguments.

    var parsed = [], value;

    if (command.encode === encode.byte) {

        if (options.command.length < 2) {

            process.stderr.write('The given command ' + name.toLowerCase() +
                ' expects argument. Try using --help.\n');
            process.exit(1);
        }

        value = parseInt(options.command[1], 10);

        if (isNaN(value) || value < 0 || value > 255) {

            process.stderr.write('The given command ' + name.toLowerCase() +
                ' expects byte (0-255) as the argument. Try using --help.\n');
            process.exit(1);
        }

        parsed.push(value);
    }

    if (command.encode === encode.control) {

        if (options.command.length < 3) {

            process.stderr.write('The given command ' + name.toLowerCase() +
                ' expects 2 arguments. Try using --help.\n');
            process.exit(1);
        }

        value = parseInt(options.command[1], 10);

        if (isNaN(value) || value < 0 || value > 255) {

            process.stderr.write('The given command ' + name.toLowerCase() +
                ' expects line index (0-4) as the first argument. Try using --help.\n');
            process.exit(1);
        }

        parsed.push(value);

        try {

            value = JSON.parse(options.command[2]);

        } catch (err) {

            process.stderr.write('The given command ' + name.toLowerCase() +
                ' expects valid JSON as the second argument. Try using --help.\n');
            process.exit(1);
        }

        parsed.push(value);
    }

    connection.open(options.port[0]).then(function(queue) {

        return queue.run(command, parsed).then(function(output) {

            // Just write the command output
            // and exit.

            if (typeof output === 'object') {

                console.log(JSON.stringify(output, null, 2));

            } else {

                console.log(output);
            }
            process.exit(0);
        });

    }).catch(function(err) {

        process.stderr.write(err.stack + '\n');
        process.exit(1);
    });
}
