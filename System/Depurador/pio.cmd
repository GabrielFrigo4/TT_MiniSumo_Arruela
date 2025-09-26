@echo OFF
setlocal

if "%~1"=="" (
	echo "options: [ build | upload | clean | monitor | erase | help ]"
	exit /b 1
)

set "arg=%~1"
set "arg=%arg:"=%"

if /i "%arg%"=="build" (
	%USERPROFILE%/.platformio/penv/Scripts/platformio run
) else if /i "%arg%"=="upload" (
	%USERPROFILE%/.platformio/penv/Scripts/platformio run --target upload
) else if /i "%arg%"=="clean" (
	%USERPROFILE%/.platformio/penv/Scripts/platformio run --target clean
) else if /i "%arg%"=="monitor" (
	%USERPROFILE%/.platformio/penv/Scripts/platformio device monitor
) else if /i "%arg%"=="erase" (
	%USERPROFILE%/.platformio/penv/Scripts/platformio run --target erase
) else if /i "%arg%"=="erase-py" (
	python -m esptool --chip esp32 erase-flash
) else if /i "%arg%"=="info-py" (
	python -m esptool --chip esp32 get-security-info
) else if /i "%arg%"=="help" (
	echo "options: [ build | upload | clean | monitor | erase | erase-py | info-py | help ]"
	exit /b 0
) else (
	echo "options: [ build | upload | clean | monitor | erase | erase-py | info-py | help ]"
	exit /b 1
)
