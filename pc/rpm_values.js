var SerialPort = require("serialport").SerialPort;
var Buffer = require('buffer').Buffer;

var serialPort = new SerialPort("/dev/ttyS1", {
    baudrate: 9600
});

serialPort.on("open", function () {

    console.log('open');

    serialPort.on('data', function(data) {

        console.log('data received: ' + data.readUInt16BE(0));
    });

    setInterval(function() {

        serialPort.write(new Buffer([3, 0]));

    }, 1000);
});
