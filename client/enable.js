var SerialPort = require("serialport").SerialPort;
var Buffer = require('buffer').Buffer;

var serialPort = new SerialPort("/dev/ttyS1", {
    baudrate: 9600
});

serialPort.on("open", function () {

    console.log('open');

    serialPort.on('data', function(data) {

        console.log('data received: ' + data.readUInt8(0));
    });

    setInterval(function() {

        serialPort.write(new Buffer([15, 0]));

    }, 1000);
});
