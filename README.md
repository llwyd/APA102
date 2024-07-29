# APA102

A tool for controlling APA102 leds using the Raspberry Pi's SPI bus.

## Usage

`blinkt.out -r 255 -g 255 -b 255 -s 100 -n 8 -d "/dev/spidev0.0"`

- r: red
- g: green
- b: blue
- s: brightness (settings)
- n: number of leds
- d: SPI device

