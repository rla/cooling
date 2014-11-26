all: main.hex eeprom.hex

main.elf: src/main.c src/*.c
	avr-gcc -std=c99 -mmcu=atmega88pa -Wall -Os -o $@ $<

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

eeprom.hex: main.elf
	avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

burn: main.hex eeprom.hex
	avrdude -c avrispmkii -p m88p -U flash:w:$(word 1,$^) -U eeprom:w:$(word 2,$^)

burn-fuse:
	avrdude -c avrispmkii -p m88p -U lfuse:w:0xf7:m

clean:
	rm -r main.hex

.PHONY: burn burn-fuse clean
