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
	platformio run --target erase

.PHONY: erase-py
erase-py:
	python -m esptool --chip esp32 erase-flash

.PHONY: info-py
info-py:
	python -m esptool --chip esp32 get-security-info
