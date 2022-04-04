.PHONY: test
test:
	pio test -e native

.PHONY: build
build:
	pio run

.PHONY: asm
asm:
	cl65 -o assembly/6502.prg --start-addr 8000 -t none --cpu 65sc02 -C assembly/6502.cfg assembly/firmware.s
	python assembly/convert-bin-include.py assembly/6502.prg > include/firmware.h

.PHONY: upload
upload: asm build
	pio run -t upload

.PHONY: run
run: upload
	pio device monitor -b 115200