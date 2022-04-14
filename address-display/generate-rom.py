

DIGITS = bytes([0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e])

with open("firmware.bin", "wb") as file:
    for index in range(0, 0x1FF):
        if (index & 0x100) == 0:  # lower bits
            byte = index & 0x00f
        else:
            byte = (index % 0x100) >> 4  # remove 9th bit and shift 4
        print("{:X} -> {:X}".format(index, DIGITS[byte]))
        file.write(bytes([DIGITS[byte]]))