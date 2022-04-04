#include "bus.h"
#include "eeprom.h"
#include "bus-monitor.h"
#include "firmware.h"

void readSerialCommand(byte in);

void setup() {
    eeprom_setup();

    Serial.begin(115200);
    delay(2);

}

void loop() {
    if (Serial.available()) {
        readSerialCommand( Serial.read() );
    }
}

void readSerialCommand(byte in)
{
    int firmware_index = 0;
    int progmem_index = 0;
    byte data;

    switch(in)  {
        case 'E' : Serial.println("CMD: E"); eeprom_eraseChip(); Serial.println("Erased"); break;
        case 'R' : Serial.println("CMD: R");
            for(unsigned int i = 0; i < FIRMWARESIZE; ++i) {
                if (i%8 == 0) {
                    Serial.println();
                    char addrText[4];
                    sprintf(addrText, "%04X", i);
                    Serial.print(addrText);
                }
                Serial.print(" ");
                Serial.print(eeprom_readData(0x0000 + i), HEX);
            }
            break;
        case 'W' : Serial.println("CMD: W");
            for(unsigned int i = 0; i < FIRMWARESIZE; ++i) {
                if (i % 32767 == 0) {
                    progmem_index = 0;
                    firmware_index++;
                }
                data = pgm_read_byte_near(FIRMWARE[firmware_index] + i);
                eeprom_programData(data, 0x0000 + i);
                if (i%8 == 0) {
                    Serial.println();
                    char addrText[4];
                    sprintf(addrText, "%04X", i);
                    Serial.print(addrText);
                }
                Serial.print(" ");
                Serial.print(data, HEX);
                progmem_index++;
            }
            Serial.println("Written");
            break;
        case 'M' : Serial.println("CMD: M"); monitor_start(); break;
        case 'm' : Serial.println("CMD: m"); monitor_stop(); break;

        default : Serial.println("E(rase); R(ead); W(rite); (M)onitor on; (m)onitor off;"); break;
    }
}
