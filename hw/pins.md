# Atmega88 pin allocation

![Atmega88 pinout](pins.png)

 * pin 20: AVCC, connected to VCC through low-pass filter L1/C13
 * pin 21: AREF, analog reference, decoupled with 100nF cap C10
 * pin 22: GND
 * pin 23: C0, ADC0, temperature sensor 1 input, low-pass filter R5/C7
 * pin 24: C1, ADC1, temperature sensor 2 input, low-pass filter R3/C8
 * pin 25: fan 1 RPM input, pull-up, low-pass filter R10/C9
 * pin 26: fan 2 RPM input, pull-up, low-pass filter R9/C11
 * pin 27: fan 3 RPM input, pull-up, low-pass filter R8/C12
 * pin 28: fan 4 RPM input, pull-up, low-pass filter R7/C14
