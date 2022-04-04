//#include "bus.h"

void eeprom_setCtrlPins();                                   //Setup control signals
void eeprom_setByte(byte out);                               //Set data across D0-D7
byte eeprom_readByte();                                      //Read byte across D0-D7
void eeprom_writeByte(byte data, unsigned long address);     //Write a byte of data at a specific address
void eeprom_programData(byte data, unsigned long address);   //Executes the program command sequence
byte eeprom_readData(unsigned long address);                 //Read data as specific address
void eeprom_eraseChip();                                     //Executes the erase chip command sequece


void eeprom_setup()
{
  setDataIn();
  eeprom_setCtrlPins();
  setAddrOut();
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
  for(int i = 0; i < 8; i++)
  {
    if (digitalRead( RD0 + i))
    {
      bitSet(temp_in, i);
    }
  }
  return temp_in;
}

void eeprom_setByte(byte out)
{
  for(int i = 0; i < 8; i++)
    digitalWrite( RD0 + i, bitRead(out, i) );
}

void eeprom_setCtrlPins()
{
  pinMode(EEPROM_WE, OUTPUT);
  pinMode(EEPROM_OE, OUTPUT);

  digitalWrite(EEPROM_WE, HIGH);
  digitalWrite(EEPROM_OE, HIGH);
}
