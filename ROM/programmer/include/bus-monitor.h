void onClock();

void monitor_start() {
    setDataIn();
    setAddrIn();

    digitalWrite(CPU_BE, HIGH); // enable bus

    attachInterrupt(digitalPinToInterrupt(CPU_CLOCK), onClock, RISING);

    Serial.println("Monitor ON");
}

void monitor_stop() {
    detachInterrupt(digitalPinToInterrupt(CPU_CLOCK));
    Serial.println("Monitor OFF");
}

void onClock() {
    Serial.print("A: ");
    char address[4];
    unsigned long addr = getAddress();
    sprintf(address, "%04X", addr);
    Serial.print(address);
    Serial.print(" b:");
    for (int i=0; i<=15; i++) {
        Serial.print(bitRead(addr, 15 - i));
    }

    Serial.print("    D: ");
    char data[2];
    sprintf(data, "%02X", getData());
    Serial.print(data);

    Serial.print(digitalRead(CPU_RW) ? "read" : "write");
    Serial.println();
}

