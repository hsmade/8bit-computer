#include "pins.h"

void setDataOut() {
    for(int i = 0; i <= 7; i++)
        pinMode(DATA_PINS[i], OUTPUT);
}

void setDataIn() {
    for(int i = 0; i <= 7; i++)
        pinMode(DATA_PINS[i], INPUT);
}

unsigned long getData() {
    unsigned long data = 0;
    int bit = 0;
    for(int i=0; i <= 7; i++) {
        bit = digitalRead(DATA_PINS[i]) ? 1 : 0;
        data = (data << 1) + bit;
    }
    return data;
}

void setData(unsigned long data) {
    for(int i = 0; i <= 7; i++)
        digitalWrite(DATA_PINS[i], bitRead(data, i));
}

void setAddress(unsigned long addr) {
    for(int i = 0; i <= 15; i++)
        digitalWrite(ADDR_PINS[i], bitRead(addr, i));
}

unsigned long getAddress() {
    unsigned long addr = 0;
    int bit = 0;
    for(int i = 0; i <= 15; i++) {
        bit = digitalRead(ADDR_PINS[15 - i]) ? 1 : 0;
        addr = (addr << 1) + bit;
    }
    return addr;
}

void setAddrOut() {
    for(int i = 0; i <= 15; i++) {
        pinMode(ADDR_PINS[i], OUTPUT);
        digitalWrite(ADDR_PINS[i], LOW);
    }
}

void setAddrIn() {
    for(int i = 0; i <= 15; i++) {
        pinMode(ADDR_PINS[i], INPUT);
    }
}
