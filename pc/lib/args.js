// Simple argument parser.

module.exports = function(args) {

    var options = {}, current, option;

    args.forEach(function(arg) {

        var match = arg.match(/^\-\-(.*)/);

        if (match) {

            option = match[1];

            current = option;

            options[option] = [];

        } else {

            if (current) {

                options[current].push(arg);
            }
        }
    });

    return options;
};
