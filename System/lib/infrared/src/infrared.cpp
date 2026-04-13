#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wvla"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wcpp"
#include <Arduino.h>
#include <IRremote.hpp>
#pragma GCC diagnostic pop
#include "infrared.hpp"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error "[ERRO]: Bluetooth is not enabled! Please run `make menuconfig` to and enable it"
#endif

#pragma region "Size Data Defines"
#ifndef BUFFER_SIZE
#error "[ERRO]: BUFFER_SIZE must be defined before compilation!"
#endif
#pragma endregion "Size Data Defines"

#pragma region "Receiver Pinning Macros"
#ifndef INFRARED_TRIGGER
#error "[ERRO]: INFRARED_TRIGGER must be defined before compilation!"
#endif
#pragma endregion "Receiver Pinning Macros"

namespace tt::infrared
{
void setup()
{
	IrReceiver.begin(INFRARED_TRIGGER, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
	printActiveIRProtocols(&Serial);
}

bool decode()
{
	return IrReceiver.decode();
}

void resume()
{
	IrReceiver.resume();
}

uint16_t command()
{
	return IrReceiver.decodedIRData.command;
}

bool update()
{
	if (decode())
	{
		resume();
		return true;
	}
	return false;
}

infrared_t receiver()
{
	switch (command())
	{
	case static_cast<uint16_t>(infrared_t::test):
		return infrared_t::test;
		break;

	case static_cast<uint16_t>(infrared_t::begin):
		return infrared_t::begin;
		break;

	case static_cast<uint16_t>(infrared_t::end):
		return infrared_t::end;
		break;

	default:
		return infrared_t::none;
		break;
	}
}

bool signal(infrared_t sig)
{
	update();
	return receiver() == sig;
}

void debug(char *out_buffer, const size_t out_size, const infrared_t infrared, const char *msg)
{
	char *rec;
	switch (infrared)
	{
	case infrared_t::test:
		rec = const_cast<char *>("test");
		break;

	case infrared_t::begin:
		rec = const_cast<char *>("begin");
		break;

	case infrared_t::end:
		rec = const_cast<char *>("end");
		break;

	default:
		rec = const_cast<char *>("none");
		break;
	}
	snprintf(
	    out_buffer,
	    out_size - 1,
	    "\"%s\" = { command:%i; infrared:\"%s\" }\n",
	    msg,
	    static_cast<uint16_t>(infrared),
	    rec
	);
}

void debug(const infrared_t infrared, const char *msg)
{
	char buffer[BUFFER_SIZE];
	debug(buffer, BUFFER_SIZE, infrared, msg);
	Serial.print(buffer);
}
} // namespace tt::infrared
