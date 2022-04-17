.PHONY: build
build:
	pio run

.PHONY: asm
asm:
	@echo running build for assembly
	$(MAKE) -C ../assembly build
	@echo converting hex file to include file
	./convert-bin-include.py ../assembly/firmware.bin > include/firmware.h

.PHONY: address-display
address-display:
	$(MAKE) -C ../bus-display build
	./convert-bin-include.py ../bus-display/rom.bin > include/firmware.h

.PHONY: upload
upload: build
	pio run -t upload

.PHONY: run
run: upload
	pio device monitor -b 115200