#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wvla"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wcpp"
#include <Arduino.h>
#pragma GCC diagnostic pop
#include "boot.hpp"
#include <serial.hpp>

namespace tt::boot
{
#pragma region "Option Data"
char boot_option = '\0';
#pragma region "Option Data"

#pragma region "Main Functions"
void setup(char start_mode)
{
	Serial.begin(115200);
	Serial.printf(STRLN("[INFO]: Serial 115200!"));

	switch (start_mode)
	{
	case BOOT_OPTION_RC:
		break;

	default:
		tt::serial::setup(ROBO_NAME);
		break;
	}
	Serial.printf(STRLN("[INFO]: Setup Serial!"));
}

void init(char start_mode)
{
	if (BOOT_OPTION_VALID(start_mode))
	{
		boot_option = start_mode;
		return;
	}

	while (!tt::serial::enabled())
	{
		vTaskDelay(1);
	}
	tt::serial::printf(STRLN("[BOOT START]"));
	tt::serial::printf(STRLN("[BOOT OPTIONS]"));
	tt::serial::printf(STRLN("[%c] Autônomo (AUTO)"), BOOT_OPTION_AUTO);
	tt::serial::printf(STRLN("[%c] Controlado (RC)"), BOOT_OPTION_RC);
	tt::serial::printf(STRLN("[%c] Depurador (DB)"), BOOT_OPTION_DB);

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

void dispose(char start_mode)
{
	if (BOOT_OPTION_VALID(start_mode))
	{
		return;
	}

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
	return BOOT_OPTION_TO_KERNEL_STATE(boot_option);
}
#pragma endregion "Boot Functions"
} // namespace tt::boot
