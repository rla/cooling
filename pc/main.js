var program = require('commander');
var version = require('./package.json').version;
var device = require('./lib/device');

program.version(version)
    .option('-p, --port [port]', 'Serial port to use.')
    .option('-q, --query [query]', 'Queries current temperature/rpm/pwm.')
    .option('-c, --command [command]', 'Enables/disables fans, sets parameters.')
    .option('-a, --arg [value]', 'Argument value for the command.')
    .parse(process.argv);

if (program.port) {

    if (program.query || program.command) {

        var d = device.open(program.port, function() {

            if (program.command === 'enable0') {

                d.enable0(handleCommand);

            } else if (program.command === 'enable1') {

                d.enable1(handleCommand);

            } else if (program.command === 'enable2') {

                d.enable2(handleCommand);

            } else if (program.command === 'enable3') {

                d.enable3(handleCommand);

            } else if (program.command === 'disable0') {

                d.disable0(handleCommand);

            } else if (program.command === 'disable1') {

                d.disable1(handleCommand);

            } else if (program.command === 'disable2') {

                d.disable2(handleCommand);

            } else if (program.command === 'disable3') {

                d.disable3(handleCommand);

            } else if (program.command === 'pwm0') {

                if (program.arg) {

                    d.setPwm0(parseInt(program.arg, 10), handleCommand);

                } else {

                    console.error('PWM command needs argument.');

                    process.exit(1);
                }

            } else if (program.command === 'pwm1') {

                if (program.arg) {

                    d.setPwm1(parseInt(program.arg, 10), handleCommand);

                } else {

                    console.error('PWM command needs argument.');

                    process.exit(1);
                }

            } else if (program.command === 'pwm2') {

                if (program.arg) {

                    d.setPwm2(parseInt(program.arg, 10), handleCommand);

                } else {

                    console.error('PWM command needs argument.');

                    process.exit(1);
                }

            } else if (program.command === 'pwm3') {

                if (program.arg) {

                    d.setPwm3(parseInt(program.arg, 10), handleCommand);

                } else {

                    console.error('PWM command needs argument.');

                    process.exit(1);
                }

            } else if (program.query === 'temp0') {

                d.temp0(handleResponse);

            } else if (program.query === 'temp1') {

                d.temp1(handleResponse);

            } else if (program.query === 'rpm0') {

                d.rpm0(handleResponse);

            } else if (program.query === 'rpm1') {

                d.rpm1(handleResponse);

            } else if (program.query === 'rpm2') {

                d.rpm2(handleResponse);

            } else if (program.query === 'rpm3') {

                d.rpm3(handleResponse);
            }
        });
    }

} else {

    console.log('Serial port is not set.');

    process.exit(1);
}

function handleResponse(err, temp) {

    if (err) {

        console.error(err.message);

        process.exit(1);

    } else {

        console.log(temp);

        // See https://github.com/voodootikigod/node-serialport/issues/241

        setTimeout(function() {

            d.close();

        }, 10);
    }
}

function handleCommand(err) {

    if (err) {

        console.error(err.message);

        process.exit(1);

    } else {

        // See https://github.com/voodootikigod/node-serialport/issues/241

        setTimeout(function() {

            d.close();

        }, 10);
    }
}
