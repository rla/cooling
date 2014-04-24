all: controller.hex

%.elf: %.c
	avr-gcc -std=c99 -mmcu=atmega88pa -Wall -Os -o $@ $<

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

burn: controller.hex
	avrdude -c avrispmkii -p m88p -U flash:w:$<

burn-usart: usart_echo.hex
	avrdude -c avrispmkii -p m88p -U flash:w:$<

burn-fuse:
	avrdude -c avrispmkii -p m88p -U lfuse:w:0xf7:m

.PHONY: burn burn-usart burn-fuse
