.PHONY: build
build:
	platformio run

.PHONY: upload
upload:
	platformio run --target upload

.PHONY: clean
clean:
	platformio run --target clean

.PHONY: monitor
monitor:
	platformio device monitor

.PHONY: erase
erase:
	python -m esptool --chip esp32 erase_flash
