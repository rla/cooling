var async = require('async');
var serialport = require('serialport');
var debug = require('debug')('connection');

// Opens connection to device
// through serialport interface.

exports.open = function(file, cb) {

    var port = new serialport.SerialPort(file, {

        baudrate: 9600,
        parser: serialport.parsers.readline('\n'),
        stopbits: 1,
        databits: 8,
        parity: 'none'
    });

    // Executed when the response is received.

    var receiver;
    var timeout;

    if (typeof cb === 'function') {

        port.on('open', cb);
    }

    port.on('data', function(data) {

        debug('Received data ' + data);

        if (receiver) {

            receiver(data);
        }

        // Disable timeout checker.

        if (timeout) {

            clearTimeout(timeout);
        }
    });

    // Commands are executed through queue.

    var queue = async.queue(function(task, cb) {

        receiver = function(data) {

            task.command.decoder(data, function(err, data) {

                if (err) {

                    task.cb(err);

                } else {

                    task.cb(null, data);
                }

                // Process next command in queue.

                cb();
            })
        };

        // Set timeout for receiving a response.

        timeout = setTimeout(function() {

            receiver = null;

            task.cb(new Error('Response timeout occurred'));

            // Process next command in queue.

            cb();

        }, 1000);

        var data = task.command.encoder();

        debug('Sending data ' + data);

        port.write(data + '\n');

    }, 1);

    var connection = {};

    // Closes the connection.

    connection.close = function(cb) {

        port.close();
    };

    // Sends given command.

    connection.send = function(command, cb) {

        queue.push({ command: command, cb: cb });
    };

    // Flushes underlying port.

    connection.flush = function(cb) {

        port.flush(cb);
    };

    return connection;
};
