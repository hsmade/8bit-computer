# CPU module
This module contains the [6502 CPU](https://eater.net/datasheets/w65c02s.pdf) and the 
[RAM](https://www.renesas.com/us/en/document/dst/71256sa-datasheet).
To decode the addresses for the RAM, a `74HC00` NAND is used.
It has a reset button, and LEDs to indicate ongoing interrupts:
- VP (vector pull) - indicates the CPU reading the interrupt vectors
- IRQ - triggers an interrupt
- NMI - triggers a non-maskable interrupt

The LEDs are mostly there for the blinkenlights effect, of course.

For the clock signal, there is a 1MHz oscillator block, a pin header for an external clock signal, 
and a switch button to do single steps. A module with 3 micro switches is used to select the clock input signal.
