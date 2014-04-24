## Internal timers

Timer0 is used for generating PWM signal for fans 1 and 2 in phase-correct PWM mode
and Timer2 is used for generating PWM signal for fans 3 and 4 in the same mode.

With a 12MHz clock the frequency of PWM signals is 12MHz/510 which is about 23.5kHz.
The [spec](http://www.formfactors.org/developer%5Cspecs%5CREV1_2_Public.pdf) says that
the PWM frequency should be in the range of 21kHz to 28KHz.

Timer1 is used for generating scheduling interrupts (each 1.04s) and measuring
the RPM count of fans.

## System interfaces

## Fan outputs

Fan outputs support 4-wire fans. PIN allocation is the following:

Fan 1

* Enable: 14/PB0
* PWM: 12/PD6/OC0A
* RPM: 25/PC2

Fan 2

* Enable: 15/PB1
* PWM: 11/PD5/OC0B
* RPM: 26/PC3

Fan 3

* Enable: 16/PB2
* PWM: 17/PB3/OC2A
* RPM: 27/PC4

Fan 4

* Enable: 18/PB4
* PWM: 5/PD3/OC2B
* RPM: 28/PC5

Fan RPM inputs have weal-pull ups connected. Inputs have low-pass filters
that increase noise immunity.

## ADC input

Two ADC inputs are enabled for measuring temperature using the
[MCP9700](http://ww1.microchip.com/downloads/en/DeviceDoc/21942e.pdf) sensors.
Sensor values are automatically converted in degrees and appear as `temp1` and
`temp2` global variables.

PIN allocation:

* Temp 1: 23/PC0/ADC0
* Temp 2: 24/PC1/ADC1

To disable these ADC inputs, change ENABLE_ADC value to 0:

    #define ENABLE_ADC_1 0
    #define ENABLE_ADC_2 0

The corresponding `temp` variable will read 0 when the ADC input is disabled.
When an ADC input is enabled and nothing is connected to it, arbitrary values
could be read from it. The ADC input should be connected to ground then or the
input should be disabled.

## USART

USART interface is enabled on the mcu. This allows to communicate with the device, control it,
and obtain the debug information. AVR USART uses TTL-level signals, therefore it cannot be directly
connected with the PC serial port. A level translator, such as [MAX232](http://www.ti.com/lit/ds/symlink/max232.pdf)
is needed. RX pin has internal pull-up set to avoid interrupts from noise when nothing is connected
to it.

To disable USART, change ENABLE_USART value to 0:

    #define ENABLE_USART 0

This will configure the port as tri-state.
