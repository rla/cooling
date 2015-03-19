var Promise = require('bluebird');
var serialport = require('serialport');
var command_queue = require('./command_queue');
var debug = require('debug')('connection');

// Opens connection to device
// through serialport interface.

exports.open = function(file, cb) {

    return new Promise(function(resolve, reject) {

        var port = new serialport.SerialPort(file, {

            baudrate: 9600,
            parser: serialport.parsers.readline('\n'),
            stopbits: 1,
            databits: 8,
            parity: 'none'
        });

        function error(err) {

            reject(err);
        }

        port.once('error', error);

        port.once('open', function() {

            port.removeListener('error', error);

            resolve(command_queue.create(port));
        });
    });
};
