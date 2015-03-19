var Promise = require('bluebird');
var command_run = require('./command_run');

// Creates command queue for
// the given port.

exports.create = function(port) {

    var queue = [], processing = false;

    function next() {

        var task = queue.shift();

        if (!task) {

            processing = false;

            return;
        }

        // Run current command.

        processing = true;

        command_run(port, task.command, task.args).then(function(data) {

            task.resolve(data);

            // Process next queue item.

            next();

        }, function(err) {

            task.reject(err);

            // Process next queue item.

            next();
        });
    }

    return {

        run: function(command, args) {

            var task = { command: command, args: args };

            queue.push(task);

            if (!processing) {

                next();
            }

            return new Promise(function(resolve, reject) {

                task.resolve = resolve;

                task.reject = reject;
            });
        },

        close: function() {

            port.close();
        }
    };
};
