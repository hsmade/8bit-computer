# tools for 6502 8 bit computer

## requirements
* cc65
* platformio

## Arduino mega 2560 connections
See [pins.h](include/pins.h) and the [Datasheet](https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf)

| Pin | Connect to | Function                                                  |
|-----|------------|-----------------------------------------------------------|
| 2   | CPU Phi2   | Clock                                                     |
| 3   | CPU RW     | Indicates bus read/write by CPU <br/>HIGH=read, LOW=write |
| 4   | CPU Reset  | When low for 2 clock cycles, resets CPU                   |
| 5   | CPU BE     | When set to low, decouples the CPU from the bus           |
| 8   | eeprom OE  | When low, enables the output on the eeprom                |
| 9   | eeprom WE  | When low, enables writing on the eeprom                   |
| 10  | eeprom CE  | When low, enables the eeprom                              |
| 22  | CPU A15    |                                                           |
| 24  | CPU A14    |                                                           |
| 26  | CPU A13    |                                                           |
| 28  | CPU A12    |                                                           |
| 30  | CPU A11    |                                                           |
| 32  | CPU A10    |                                                           |
| 34  | CPU A9     |                                                           |
| 36  | CPU A8     |                                                           |
| 38  | CPU A7     |                                                           |
| 40  | CPU A6     |                                                           |
| 42  | CPU A5     |                                                           |
| 44  | CPU A4     |                                                           |
| 46  | CPU A3     |                                                           |
| 48  | CPU A2     |                                                           |
| 50  | CPU A1     |                                                           |
| 52  | CPU A0     |                                                           |
| 39  | CPU D7     |                                                           |
| 41  | CPU D6     |                                                           |
| 43  | CPU D5     |                                                           |
| 45  | CPU D4     |                                                           |
| 47  | CPU D3     |                                                           |
| 49  | CPU D2     |                                                           |
| 51  | CPU D1     |                                                           |
| 53  | CPU D0     |                                                           |

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
