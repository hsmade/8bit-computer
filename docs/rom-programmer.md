# EEPROM programmer

This Arduino firmware can be loaded onto an Arduino Mega, to program the EEPROM.
The EEPROM used in this program is of the `sst39sf0x0` family.

## Usage
First, you'll need to create the `firmware.h`, which contains the ROM image, as a byte array.
This can be generated with the script [`convert-bin-include.py`](https://github.com/hsmade/8bit-computer/blob/master/ROM/programmer/convert-bin-include.py).

The [`Makefile`](https://github.com/hsmade/8bit-computer/blob/master/ROM/programmer/Makefile) in this repo contains targets for the use cases in this repo.
See the contents of the Makefile for more options.

Building the assembly code and running the programmer:
```bash
make asm run
```

The programmer will present you some options to:
 * (r)ead an address
 * (w)rite an address
 * (E)rase the EEPROM
 * (W)rite the firmware.h contents to the EEPROM
 * (R)ead the contents of the EEPROM (uses the size of the firmware.h array)

Note that currently, the programmer starts writing from `0x8000` when writing the firmware!

## Arduino mega 2560 connections
The pins are defined in [`include/pins.h`](https://github.com/hsmade/8bit-computer/blob/master/ROM/programmer/include/pins.h).
The CPU connections are not used when handling the EEPROM, 
they are there to support monitoring the CPU bus.


| Pin | Connect to | Function                                                  |
|-----|------------|-----------------------------------------------------------|
| 2   | CPU Phi2   | Clock                                                     |
| 3   | CPU RW     | Indicates bus read/write by CPU <br/>HIGH=read, LOW=write |
| 4   | CPU Reset  | When low for 2 clock cycles, resets CPU                   |
| 5   | CPU BE     | When set to low, decouples the CPU from the bus           |
| 8   | eeprom OE  | When low, enables the output on the eeprom                |
| 9   | eeprom WE  | When low, enables writing on the eeprom                   |
| 10  | eeprom CE  | When low, enables the eeprom                              |
| 53  | A15        |                                                           |
| 51  | A14        |                                                           |
| 49  | A13        |                                                           |
| 47  | A12        |                                                           |
| 45  | A11        |                                                           |
| 43  | A10        |                                                           |
| 41  | A9         |                                                           |
| 39  | A8         |                                                           |
| 37  | A7         |                                                           |
| 35  | A6         |                                                           |
| 33  | A5         |                                                           |
| 31  | A4         |                                                           |
| 29  | A3         |                                                           |
| 27  | A2         |                                                           |
| 25  | A1         |                                                           |
| 23  | A0         |                                                           |
| 38  | D7         |                                                           |
| 40  | D6         |                                                           |
| 42  | D5         |                                                           |
| 44  | D4         |                                                           |
| 46  | D3         |                                                           |
| 48  | D2         |                                                           |
| 50  | D1         |                                                           |
| 52  | D0         |                                                           |
