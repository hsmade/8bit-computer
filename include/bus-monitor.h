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
    char[4] address;
    sprintf(address, "%04X", getAddress())
    Serial.print(address);

    Serial.print("    D: ");
    char[2] data;
    sprintf(data, "%02X", getData())
    Serial.print(data);

    Serial.print("    RW: ");
    Serial.print(digitalRead(RW) ? 'r' : 'w');

    Serial.println();
}

