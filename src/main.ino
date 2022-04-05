#include "bus.h"
#include "eeprom.h"
#include "bus-monitor.h"
#include "firmware.h"

unsigned long readLongFromSerial(int len);
void readSerialCommand(byte in);

void setup() {
    Serial.begin(115200);

    pinMode(CPU_RW, INPUT);
    pinMode(CPU_CLOCK, INPUT);
    pinMode(CPU_BE, OUTPUT);
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
    long address;

    switch(in)  {
        case 'E' : Serial.println("CMD: E"); eeprom_setup();eeprom_eraseChip(); Serial.println("Erased"); break;
        case 'R' : Serial.println("CMD: R");
            eeprom_setup();
            for(unsigned int i = 0; i < FIRMWARESIZE; i++) {
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
            eeprom_setup();
            for(unsigned int i = 0; i < FIRMWARESIZE; i++) {
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
        case 'r' : Serial.println("CMD: read address: ");
            address = readLongFromSerial(4);
            Serial.print("got address: ");
            Serial.println(address, HEX);
            Serial.print("data: ");
            setAddress(address);

            eeprom_setCtrlPins();
            Serial.println(eeprom_readData(address), HEX);
            eeprom_unSetCtrlPins();

        default : Serial.println("E(rase); R(ead); W(rite); (M)onitor on; (m)onitor off;"); break;
    }
}

unsigned long readLongFromSerial(int len) {
    char buffer[len+3];
    buffer[0] = '0';
    buffer[1] = 'x';
    for (int i=2;i<len+2;i++) {
        while(Serial.available() == 0);
        buffer[i] = Serial.read();
    }
    buffer[len+2] = '\0';
    long result = strtoul(buffer, NULL, 0);
    return result;
}
