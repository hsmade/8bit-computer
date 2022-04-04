//#include "bus.h"

void onClock();

void monitor_start() {
    setDataIn();
    setAddrIn();

    pinMode(RW, INPUT);
    pinMode(CLOCK, INPUT);

    attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

    Serial.println("Monitor ON");
}

void monitor_stop() {
    detachInterrupt(digitalPinToInterrupt(CLOCK));
    Serial.println("Monitor OFF");
}

void onClock() {
    Serial.print("A: ");
    char address[4];
    unsigned long addr = getAddress();
    sprintf(address, "%04X", addr);
    Serial.print(address);
    Serial.print(" b:");
    for (int b = 15; b >=0; b--) {
        Serial.print(bitRead(addr, b));
    }

    Serial.print("    D: ");
    char data[2];
    sprintf(data, "%02X", getData());
    Serial.print(data);

    Serial.print("    RW: ");
    Serial.print(digitalRead(RW) ? 'r' : 'w');

    Serial.println();
}

