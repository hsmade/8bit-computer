#define EEPROM_OE 8
#define EEPROM_WE 9
#define EEPROM_CE 10

const char ADDR_PINS[] = {22, 24, 26, 28, 30, 32 ,34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const char DATA_PINS[] = {39, 41, 43, 45, 47, 49, 51, 53};

#define CPU_CLOCK 2
#define CPU_RW    3
#define CPU_RESET 4
#define CPU_BE    5
