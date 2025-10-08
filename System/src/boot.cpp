#include <Arduino.h>
#include <serial.hpp>
#include "boot.hpp"

namespace tt::boot
{
#pragma region "Option Data"
	char boot_option = '\0';
#pragma region "Option Data"

#pragma region "Main Functions"
	void setup()
	{
		Serial.begin(115200);
		Serial.printf(STRLN("Serial 115200!"));

		tt::serial::setup(ROBO_NAME);
		Serial.printf(STRLN("Setup Serial!"));
	}

	void init()
	{
		while (!tt::serial::enabled())
		{
			vTaskDelay(1);
		}
		tt::serial::printf(STRLN("[BOOT START]"));
		tt::serial::printf(STRLN("[BOOT OPTIONS]"));
		tt::serial::printf(STRLN("[1] Autônomo (AUTO)"));
		tt::serial::printf(STRLN("[2] Controlado (RC)"));
		tt::serial::printf(STRLN("[3] Depurador (DB)"));

		while (!BOOT_OPTION_VALID(boot_option))
		{
			vTaskDelay(1);
			if (tt::serial::available())
			{
				boot_option = tt::serial::read();
				switch (boot_option)
				{
				case BOOT_OPTION_AUTO:
					tt::serial::printf(STRLN("+------+------+"));
					tt::serial::printf(STRLN("| BOOT | AUTO |"));
					tt::serial::printf(STRLN("+------+------+"));
					break;
				case BOOT_OPTION_RC:
					tt::serial::printf(STRLN("+------+----+"));
					tt::serial::printf(STRLN("| BOOT | RC |"));
					tt::serial::printf(STRLN("+------+----+"));
					break;
				case BOOT_OPTION_DB:
					tt::serial::printf(STRLN("+------+----+"));
					tt::serial::printf(STRLN("| BOOT | DB |"));
					tt::serial::printf(STRLN("+------+----+"));
					break;
				default:
					tt::serial::printf(STRLN("[ERRO]: Invalid input, try again."));
					break;
				}
				tt::serial::erase();
			}
			else
			{
				continue;
			}
		}
	}

	void dispose()
	{
		vTaskDelay(1024);
		switch (boot_option)
		{
		case BOOT_OPTION_AUTO:
			tt::serial::clear();
			break;
		case BOOT_OPTION_RC:
			tt::serial::end();
			vTaskDelay(512);
			break;
		case BOOT_OPTION_DB:
			tt::serial::clear();
			break;
		default:
			break;
		}
		vTaskDelay(64);
	}
#pragma endregion "Main Functions"

#pragma region "Boot Functions"
	uint8_t get_boot()
	{
		return BOOT_OPTION_TO_STATE(boot_option);
	}
#pragma endregion "Boot Functions"
}
