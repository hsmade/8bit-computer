#define EEPROM_OE 8
#define EEPROM_WE 9
#define EEPROM_CE 10

//                        00                          08                              16
const char ADDR_PINS[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};
const char DATA_PINS[] = {52, 50, 48, 46, 44, 42, 40, 38};

#define CPU_CLOCK 2
#define CPU_RW    3
#define CPU_RESET 4
#define CPU_BE    5
