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
        case '0' : Serial.println("data 0"); eeprom_setup();setData(0x01); break;
        case '1' : Serial.println("data 1"); eeprom_setup();setData(0x02); break;
        case '2' : Serial.println("data 2"); eeprom_setup();setData(0x04); break;
        case '3' : Serial.println("data 3"); eeprom_setup();setData(0x08); break;
        case '4' : Serial.println("data 4"); eeprom_setup();setData(0x10); break;
        case '5' : Serial.println("data 5"); eeprom_setup();setData(0x20); break;
        case '6' : Serial.println("data 6"); eeprom_setup();setData(0x40); break;
        case '7' : Serial.println("data 7"); eeprom_setup();setData(0x80); break;
        case 'R' : Serial.println("CMD: R");
            eeprom_setup();
            for(unsigned int i = 0; i < FIRMWARESIZE; i++) {
                if (i%8 == 0) {
                    Serial.println();
                    char addrText[4];
                    sprintf(addrText, "%04X", 0x8000 + i);
                    Serial.print(addrText);
                }
                Serial.print(" ");
                Serial.print(eeprom_readData(0x8000 + i), HEX);
            }
            break;
        case 'W' : Serial.println("CMD: W");
            eeprom_setup();
            for(unsigned int address = 0; address < FIRMWARESIZE; address++) {
                if (address >0 && address % 32767 == 0) {
                    progmem_index = 0;
                    firmware_index++;
                }

                data = pgm_read_byte_near(&FIRMWARE[firmware_index][progmem_index]);
                eeprom_programData(data, 0x8000 + address);

                if (address % 8 == 0) {
                    Serial.println();
                    char addrText[4];
                    sprintf(addrText, "%04X", 0x8000 + address);
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
