# tools for 6502 8 bit computer

## requirements
* cc65
* platformio

## Arduino mega 2560 connections
See [pins.h](include/pins.h) and the [Datasheet](https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf)

| Pin | Connect to | Function                                                  |
|--|------------|-----------------------------------------------------------|
| 2 | CPU Phi2   | Clock                                                     |
| 3 | CPU RW     | Indicates bus read/write by CPU <br/>HIGH=read, LOW=write |
| 4 | CPU Reset  | When low for 2 clock cycles, resets CPU                   |
| 5 | CPU BE     | When set to low, decouples the CPU from the bus           |
| 8 | eeprom OE  | When low, enables the output on the eeprom                |
| 9 | eeprom WE  | When low, enables writing on the eeprom                   |
| 10 | eeprom CE  | When low, enables the eeprom                              |
| 53 | CPU A15    |                                                           |
| 51 | CPU A14    |                                                           |
| 49 | CPU A13    |                                                           |
| 47 | CPU A12    |                                                           |
| 45 | CPU A11    |                                                           |
| 43 | CPU A10    |                                                           |
| 41 | CPU A9     |                                                           |
| 39 | CPU A8     |                                                           |
| 37 | CPU A7     |                                                           |
| 35 | CPU A6     |                                                           |
| 33 | CPU A5     |                                                           |
| 31 | CPU A4     |                                                           |
| 29 | CPU A3     |                                                           |
| 27 | CPU A2     |                                                           |
| 25 | CPU A1     |                                                           |
| 23 | CPU A0     |                                                           |
| 38 | CPU D7     |                                                           |
| 40 | CPU D6     |                                                           |
| 42 | CPU D5     |                                                           |
| 44 | CPU D4     |                                                           |
| 46 | CPU D3     |                                                           |
| 48 | CPU D2     |                                                           |
| 50 | CPU D1     |                                                           |
| 52 | CPU D0     |                                                           |

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

## Schematic
![schematic](kicad/8bit-cpu-address-decoder.svg)