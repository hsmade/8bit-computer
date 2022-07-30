#define EEPROM_OE 31
#define EEPROM_WE 33
#define EEPROM_CE 35

//                        00                          08                              16
const char ADDR_PINS[] = {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 27, 29};
const char DATA_PINS[] = {39, 41, 43, 45, 47, 49, 51, 53};

#define CPU_CLOCK 2
#define CPU_RW    3
#define CPU_RESET 4
#define CPU_BE    5
