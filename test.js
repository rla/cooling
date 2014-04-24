var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyS1", {
    baudrate: 9600
});

serialPort.on("open", function () {
    
    console.log('open');
    
    serialPort.on('data', function(data) {
        
        console.log('data received: ' + parseInt(data.toString('hex'), 16));
    });
  
    setInterval(function() {
        
        serialPort.write('a');
        
    }, 1000);
});
