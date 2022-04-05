//#include "bus.h"

void eeprom_setCtrlPins();                                   //Setup control signals
void eeprom_unSetCtrlPins();                                 //Setup control signals
void eeprom_setByte(byte out);                               //Set data across D0-D7
byte eeprom_readByte();                                      //Read byte across D0-D7
void eeprom_writeByte(byte data, unsigned long address);     //Write a byte of data at a specific address
void eeprom_programData(byte data, unsigned long address);   //Executes the program command sequence
byte eeprom_readData(unsigned long address);                 //Read data as specific address
void eeprom_eraseChip();                                     //Executes the erase chip command sequece


void eeprom_setup()
{
    eeprom_setCtrlPins();
    setDataIn();
    setAddrOut();
    digitalWrite(CPU_BE, LOW); // disable bus

}

void eeprom_teardown() {
    eeprom_unSetCtrlPins();
    setDataIn();
    setAddrOut();
    digitalWrite(CPU_BE, HIGH); // enable bus
}

void eeprom_eraseChip()
{
  setDataOut();

  eeprom_writeByte(0xAA, 0x5555);
  eeprom_writeByte(0x55, 0x2AAA);
  eeprom_writeByte(0x80, 0x5555);
  eeprom_writeByte(0xAA, 0x5555);
  eeprom_writeByte(0x55, 0x2AAA);
  eeprom_writeByte(0x10, 0x5555);

  delay(100);
  setDataIn();
}

byte eeprom_readData(unsigned long address)
{
  byte temp_read;
  setDataIn();

  digitalWrite(EEPROM_WE, HIGH);
  digitalWrite(EEPROM_OE, HIGH);

  setAddress(address);

  digitalWrite(EEPROM_OE, LOW);
  delayMicroseconds(1);

  temp_read = eeprom_readByte();

  digitalWrite(EEPROM_OE, HIGH);

  return temp_read;
}

void eeprom_writeByte(byte data, unsigned long address)
{
  digitalWrite(EEPROM_OE, HIGH);
  digitalWrite(EEPROM_WE,HIGH);

  setAddress(address);
  eeprom_setByte(data);

  digitalWrite(EEPROM_WE, LOW);
  delayMicroseconds(1);
  digitalWrite(EEPROM_WE, HIGH);
}

void eeprom_programData(byte data, unsigned long address)
{
  setDataOut();

  eeprom_writeByte(0xAA, 0x5555);
  eeprom_writeByte(0x55, 0x2AAA);
  eeprom_writeByte(0xA0, 0x5555);
  eeprom_writeByte(data, address);

  delayMicroseconds(30);
}

byte eeprom_readByte()
{
  byte temp_in = 0;
  for(int i=0; i <= 7; i++) {
    if (digitalRead(DATA_PINS[i])) {
      bitSet(temp_in, 7 - i);
    }
  }
  return temp_in;
}

void eeprom_setByte(byte out)
{
  for(int i=0; i <= 7; i++)
    digitalWrite(DATA_PINS[i], bitRead(out, 7 - i));
}

void eeprom_setCtrlPins()
{
  pinMode(EEPROM_CE, OUTPUT);
  pinMode(EEPROM_WE, OUTPUT);
  pinMode(EEPROM_OE, OUTPUT);

  digitalWrite(EEPROM_CE, LOW);
  digitalWrite(EEPROM_WE, HIGH);
  digitalWrite(EEPROM_OE, HIGH);
}

void eeprom_unSetCtrlPins()
{
  digitalWrite(EEPROM_CE, HIGH); // to be pulled down by inverter on A15
  digitalWrite(EEPROM_WE, HIGH);
  digitalWrite(EEPROM_OE, HIGH); // to be pulled down by inverter on A15

  pinMode(EEPROM_CE, INPUT);
  pinMode(EEPROM_WE, INPUT);
  pinMode(EEPROM_OE, INPUT);
}
