# cooling

PC cooling controller for rotary cooling devices (fans/pumps). It has
the following features:

 * Supports 4 cooling devices.
 * Can disable devices that still run on minimal PWM.
 * Monitors devices RPM.
 * RPM measurement supports pulse stretching.
 * Supports 2 analog sensory devices on ADC.
 * Error signal output.
 * Can be controlled/queried over RS-232 interface.
 * NodeJS library to manipulate the device from PC.
 * Hardware design and source code is MIT-licensed.

The project is still work-in-progress.

## Hardware

### Building

To build the HEX binary for the controller:

    cd avr
    make

## Changelog

 * 2014-02-01 Physical hardware design is ready.

## License

The MIT License. See the LICENSE file.
