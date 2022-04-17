# My 8-bit computer

This repo describes my homebrew 8-bit computer. 
It is loosely based on the works of  [Ben eater's 6502 computer](https://eater.net/6502), and others.

A build log can be found [here](build-log/README.md)

## Components
### CPU card
This card contains the CPU and the RAM.

To be built.

* more info [here](CPU/README.md)
* the schematics can be found [here](CPU/kicad/)

### ROM card
This card holds the rom, and exposes a pin header for programming.
I currently do the programming with an Arduino Mega (because I need a lot of IO ports).
The software for programming the eeprom can be found [here](ROM/programmer/README.md)

* more info [here](ROM/README.md).
* the schematic can be found [here](ROM/kicad/).

### Bus display card
This card shows the current contents of the address and data bus, and if the CPU is reading or writing.
I used the trick to alternate between 2 displays, using a timer, from Ben Eater.
This doesn't use the whole flip-flop setup though, as I use just 2 displays per 8 bits (hex).

* more info [here](bus-display/README.md)
* the schematic can be found [here](bus-display/kicad/).

### IO card
This card will interface with the outside world.
The idea is to control a 1602A display, and a serial port.

To be designed and built.

## Requirements
The following software is required to run makefiles:
* cc65
* platformio

## Memory map
http://wilsonminesco.com/6502primer/addr_decoding.html
![address decoder](address-decoder.jpg)


| start | end  | what     |
|-------|------|----------|
| 0000  | 3FFF | RAM      |
| 4100  |      | ACIA 3-1 |
| 4104  |      | ACIA 3-2 |
| 4108  |      | ACIA 3-3 |
| 410C  |      | ACIA 3-4 |
| 4200  |      | ACIA 2-1 |
| 4204  |      | ACIA 2-2 |
| 4208  |      | ACIA 2-3 |
| 420C  |      | ACIA 2-4 |
| 4400  | 4403 | ACIA 1   |
| 4800  | 480F | VIA 3    |
| 5000  | 500F | VIA 2    |
| 6000  | 600F | VIA 1    |
| 8000  | FFFF | ROM      |


## Bus

| Use | Port | Port | Use   |
|-----|------|------|-------|
| VSS | 1    | 40   | VSS   |
| X   | 2    | 39   | X     |
| X   | 3    | 38   | X     |
| +5V | 4    | 37   | +5V   |
| A0  | 5    | 36   | X     |
| A1  | 6    | 35   | X     |
| A2  | 7    | 34   | RES   |
| A3  | 8    | 33   | NMI   |
| A4  | 9    | 32   | IRQ   |
| A5  | 10   | 31   | Phi 1 |
| A6  | 11   | 30   | Phi 2 |
| A7  | 12   | 29   | R/W   |
| A8  | 13   | 28   | D7    |
| A9  | 14   | 27   | D6    |
| A10 | 15   | 26   | D5    |
| A11 | 16   | 25   | D4    |
| A12 | 17   | 24   | D3    |
| A13 | 18   | 23   | D2    |
| A14 | 19   | 22   | D1    |
| A15 | 20   | 21   | D0    |
