# tools for 6502 8 bit computer

## requirements
* cc65
* platformio

## Arduino mega 2560 connections
See [pins.h](include/pins.h)

| Pin    | Connect to             |
|--------|------------------------|
| 2      | CPU Clock              |
| 3      | eeprom OE              |
| 4      | CPU RW                 |
| 5      | eeprom WE              |
| 6      | CPU Reset              |
| 7      | CPU IRQ                |
| 8      | CPU NMI                |
| 9      | CPU RDY                |
| 10     | CPU SYNC               |
| 11     | CPU SO                 |
| 12     | eeprom CE              |
| 22..38 | Address lines A00..A16 |
| 44..51 | Data lines DQ0..DQ7    |

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
