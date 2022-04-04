#include "pins.h"

void setDataOut() {
    for(int i = RD0; i <= RD7; i++)
        pinMode(i, OUTPUT);
}

void setDataIn() {
    for(int i = RD0; i <= RD7; i++)
        pinMode(i, INPUT);
}

unsigned long getData() {
    unsigned long data = 0;
    int bit = 0;
    for(int i = 7; i >= 0; i--) {
        bit = digitalRead(RD0 + i) ? 1 : 0;
        data = (data << 1) + bit;
    }
    return data;
}

void setData(unsigned long data) {
    for(int i = 0; i < 9; i++)
        digitalWrite( RD0 + i , bitRead(data, i) );
}

void setAddress(unsigned long addr) {
    for(int i = 0; i < 16; i++)
        digitalWrite( RA0 + i , bitRead(addr, i) );
}

unsigned long getAddress() {
    unsigned long addr = 0;
    int bit = 0;
    for(int i = 15; i >= 0; i--) {
        bit = digitalRead(RA0 + i) ? 1 : 0;
        addr = (addr << 1) + bit;
    }
    return addr;
}

void setAddrOut() {
      for(int i = RA0; i <= RA15; i++) {
            pinMode(i, OUTPUT);
            digitalWrite(i, LOW);
      }
}

void setAddrIn() {
      for(int i = RA0; i <= RA15; i++) {
            pinMode(i, INPUT);
      }
}
