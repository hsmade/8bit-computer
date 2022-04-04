#!/usr/bin/env python
import sys

print("const static byte FIRMWARE0[] PROGMEM = {")

size = 0
total_size = 0
index = 0
with open(sys.argv[1]) as f:
    while (byte := f.buffer.read(1)):
        size += 1
        total_size += 1
        if size > 32767:
            size = 0
            index += 1
            print("};")
            print("const byte FIRMWARE%d[] PROGMEM = {" % index)

        print("0x" + byte.hex() + ",")

print("};")

print("const byte* FIRMWARE[%d] = {" % (index+1), ", ".join(["FIRMWARE{}".format(i) for i in range(0, index+1)]), "};")
print("unsigned int FIRMWARESIZE = %d;" % total_size)
