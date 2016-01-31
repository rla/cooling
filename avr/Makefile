all: main.hex eeprom.hex

main.elf: src/main.c src/*.c
	avr-gcc -std=c99 -mmcu=atmega88pa -Wall -Os -o $@ $<

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

eeprom.hex: main.elf
	avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

burn: main.hex eeprom.hex
	avrdude -c avrispmkii -p m88p -U flash:w:$(word 1,$^) -U eeprom:w:$(word 2,$^)

# Full-swing crystal, BOD enabled
# BOD 4.3V
#
# Low fuse
# CKDIV8 1 (unprogrammed)
# CKOUT 1 (unprogrammed)
# SUT1 0 (crystal, BOD enabled)
# SUT0 1 (crystal, BOD enabled)
# CKSEL3 0
# CKSEL2 1
# CKSEL1 1
# CKSEL0 1
#
# CKSEL is for full-swing crystal osc.
# lfuse total 11010111 = 0xd7
#
# High fuse
#
# RSTDISBL 1 (unprogrammed)
# DWEN 1 (unprogrammed)
# SPIEN 0 (programmed)
# WDTON 1 (unprogrammed)
# EESAVE 1 (unprogrammed)
# BODLEVEL2 1
# BODLEVEL1 0
# BODLEVEL0 0
#
# hfuse total 11011100 = 0xdc

burn-fuse:
	avrdude -c avrispmkii -p m88p -U lfuse:w:0xd7:m -U hfuse:w:0xdc:m

clean:
	rm -r main.hex

.PHONY: burn burn-fuse clean
