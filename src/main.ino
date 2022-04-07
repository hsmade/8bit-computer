#include "bus.h"
#include "eeprom.h"
#include "bus-monitor.h"
#include "firmware.h"

unsigned long readLongFromSerial(int len);
void readSerialCommand(byte in);

void setup() {
    Serial.begin(115200);
    delay(3);
    Serial.println("Started");

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
//             for(unsigned int i = 0; i < 3; i++) {
                if (i % 32767 == 0) {
                    progmem_index = 0;
                    firmware_index++;
                }
                data = pgm_read_byte_near(FIRMWARE[firmware_index] + 1 + i);
                eeprom_programData(data, 0x0000 + i);
                Serial.print("Written ");
                Serial.print(data, HEX);
                Serial.print(" to ");
                Serial.println(0x0000 + i, HEX);
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
            eeprom_setup();
            address = readLongFromSerial(4);
            Serial.print("got address: ");
            Serial.println(address, HEX);
            Serial.print("data: ");
            Serial.println(eeprom_readData(address), HEX);
//             digitalWrite(CPU_BE, LOW);
//             setAddress(address);
//             delay(1000);
//             Serial.println(getData(), HEX);
//             digitalWrite(CPU_BE, HIGH);
            break;
        case 'w' : Serial.println("CMD: write address: ");
            eeprom_setup();
            address = readLongFromSerial(4);
//             Serial.print("got address: ");
            Serial.println(address, HEX);
            Serial.print("write data: ");
            data = readLongFromSerial(2);

//             digitalWrite(CPU_BE, LOW);
//             eeprom_setCtrlPins();
            Serial.print("writing ");
            Serial.print(data, HEX);
            Serial.print(" to ");
            Serial.println(address, HEX);
            eeprom_programData(data, address);
//             delay(1000);
//             Serial.println("stopping eeprom");
//             eeprom_teardown();
//             delay(1000);
            Serial.println("done");
//             digitalWrite(CPU_BE, HIGH);
            break;

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
