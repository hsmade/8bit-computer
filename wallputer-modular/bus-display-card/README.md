# Bus Display Card

This card displays the contents of the address and the data bus in hexadecimals using the 7-segment displays.
The way this works is that each 'address' in the EEPROM has a value that corresponds to the right segments 
on the display. So for example, address 8 has value FE, so it lits up all segments.
The A8 signal is fed a square wave, so half the time we're using 0000-00FF and the 'right' display corresponding
to the right most byte, and the other half we're using FF00-FFFF and the 'left' display.
This way, we can re-use 1 EEPROM for 2 bytes data.

See [display-table.md](display-table.md) for a mapping. Use the script/makefie to generate the EEPROM binary.

![Bus display card schematic](renders/bus-display-card.svg)

![Bus display card PCB](renders/bus-display-card-pcb.svg)
