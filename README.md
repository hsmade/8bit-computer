# My 8-bit computer

This repo describes my homebrew 8-bit computer. 
It is loosely based on the works of  [Ben eater's 6502 computer](https://eater.net/6502), and others.

A build log can be found [here](https://hsmade.github.io/8bit-computer)

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


| start | end  | what     | A15 | A14 | 
|-------|------|----------|-----|-----|
| 0000  | 3FFF | RAM      |   0 |   0 | 
| 4100  |      | ACIA 3-1 |   0 |   1 |
| 4104  |      | ACIA 3-2 |   0 |   1 |
| 4108  |      | ACIA 3-3 |   0 |   1 |
| 410C  |      | ACIA 3-4 |   0 |   1 |
| 4200  |      | ACIA 2-1 |   0 |   1 |
| 4204  |      | ACIA 2-2 |   0 |   1 |
| 4208  |      | ACIA 2-3 |   0 |   1 |
| 420C  |      | ACIA 2-4 |   0 |   1 |
| 4400  | 4403 | ACIA 1   |   0 |   1 |
| 4800  | 480F | VIA 3    |   0 |   1 |
| 5000  | 500F | VIA 2    |   0 |   1 |
| 6000  | 600F | VIA 1    |   0 |   1 |
| 8000  | FFFF | ROM      |   1 |   x |


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

## Datasheets
* NAND [74HC00](https://www.mouser.com/catalog/specsheets/nxp_74hc_hct00.pdf)
* CPU [W65C02](https://nl.mouser.com/datasheet/2/436/w65c02s-2572.pdf)
* Power transistor PNP [BD952](https://nl.mouser.com/datasheet/2/54/bd646-1159083.pdf)
* RAM [39SF010A7CPHE](https://nl.mouser.com/datasheet/2/268/20005022C-1832260.pdf)
* 7 segment display [INND-TS40Y*CB](https://nl.mouser.com/datasheet/2/180/INND-TS40_Series_V1.0-1485199.pdf)
* ROM [SST39SF010A](https://nl.mouser.com/datasheet/2/268/20005022C-1832260.pdf)
* ACIA [W65C51](https://nl.mouser.com/datasheet/2/436/WDC_Datasheet%20Update_20141024-1211725.pdf)
* PIO [W65C22](https://nl.mouser.com/datasheet/2/436/w65c22-1197.pdf)
