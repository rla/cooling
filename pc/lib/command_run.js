var Promise = require('bluebird');
var debug = require('debug')('command');

// Helper to run single command on
// the connection.

module.exports = function(port, command, args) {

    return new Promise(function(resolve, reject) {

        debug('Encoding command ' + command.id);

        if (typeof args !== 'undefined') {

            debug('Command arguments are ' + args);
        }

        var actual = args.slice(0);

        actual.unshift(command.id);

        var encoded = command.encode.apply(null, actual);

        var handler = function(line) {

            debug('Received ' + line);

            clearTimeout(timeout);

            resolve(command.decode(line));
        };

        port.once('data', handler);

        var timeout = setTimeout(function() {

            port.removeListener('data', handler);

            reject(new Error('Response timeout.'));

        }, 1000);

        debug('Sending ' + encoded);

        port.write(encoded + '\n');
    });
};
