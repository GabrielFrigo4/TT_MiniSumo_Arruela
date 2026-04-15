#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wvla"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wcpp"
#include <Arduino.h>
#pragma GCC diagnostic pop
#include "engine.hpp"
#include "utilities.hpp"

#pragma region "Size Data Defines"
#ifndef BUFFER_SIZE
#error "[ERRO]: BUFFER_SIZE must be defined before compilation!"
#endif
#pragma endregion "Size Data Defines"

#pragma region "Analog Data Defines"
#ifndef ANALOG_LEN
#define ANALOG_LEN 8
#endif
#ifndef ANALOG_LOW
#define ANALOG_LOW 0
#endif
#ifndef ANALOG_HIGH
#define ANALOG_HIGH ((1 << ANALOG_LEN) - 1)
#endif
#ifndef ANALOG_HZ
#define ANALOG_HZ (1 << 14)
#endif
#pragma endregion "Analog Data Defines"

#pragma region "Engine Pinning Macros"
#ifndef ENGINE_LEFT_1
#error "[ERRO]: ENGINE_LEFT_1 must be defined before compilation!"
#endif
#ifndef ENGINE_LEFT_2
#error "[ERRO]: ENGINE_LEFT_2 must be defined before compilation!"
#endif
#ifndef ENGINE_RIGHT_1
#error "[ERRO]: ENGINE_RIGHT_1 must be defined before compilation!"
#endif
#ifndef ENGINE_RIGHT_2
#error "[ERRO]: ENGINE_RIGHT_2 must be defined before compilation!"
#endif
#pragma endregion "Engine Pinning Macros"

#pragma region "Engine Legacy Pinning Macros"
#if !defined MODERN_ELECTRONICS
#ifndef ENGINE_LEFT_PWM
#error "[ERRO]: ENGINE_LEFT_PWM must be defined before compilation!"
#endif
#ifndef ENGINE_RIGHT_PWM
#error "[ERRO]: ENGINE_RIGHT_PWM must be defined before compilation!"
#endif
#ifndef ENGINE_STANDBY
#error "[ERRO]: ENGINE_STANDBY must be defined before compilation!"
#endif
#endif
#pragma endregion "Engine Legacy Pinning Macros"

#pragma region "Engine Macros"
#define PIN_BOOL(x) ((HIGH) * (x) + (LOW) * !(x))
#pragma endregion "Engine Macros"

namespace tt::engine
{
engine_t current_engine_left = TT_ENGINE_DEFAULT;
engine_t current_engine_right = TT_ENGINE_DEFAULT;
bool standby_mode = true;

static void h_bridge_write(uint8_t pin, int value)
{
	analogWrite(pin, value * !standby_mode);
}

#if defined MODERN_ELECTRONICS
static void setup_modern()
{
	// analogWriteResolution(ANALOG_LEN);
	// analogWriteFrequency(ANALOG_HZ);
	pinMode(ENGINE_LEFT_1, OUTPUT);
	pinMode(ENGINE_LEFT_2, OUTPUT);
	pinMode(ENGINE_RIGHT_1, OUTPUT);
	pinMode(ENGINE_RIGHT_2, OUTPUT);
	set_standby(true);
}
#endif

#if !defined MODERN_ELECTRONICS
static void setup_legacy()
{
	pinMode(ENGINE_LEFT_PWM, OUTPUT);
	pinMode(ENGINE_LEFT_1, OUTPUT);
	pinMode(ENGINE_LEFT_2, OUTPUT);
	pinMode(ENGINE_RIGHT_PWM, OUTPUT);
	pinMode(ENGINE_RIGHT_1, OUTPUT);
	pinMode(ENGINE_RIGHT_2, OUTPUT);
	pinMode(ENGINE_STANDBY, OUTPUT);
	set_standby(true);
}
#endif

void setup()
{
#if defined MODERN_ELECTRONICS
	setup_modern();
#else
	setup_legacy();
#endif
}

#if defined MODERN_ELECTRONICS
static void init_modern()
{
	set_standby(false);

	current_engine_left = TT_ENGINE_DEFAULT;
	h_bridge_write(ENGINE_LEFT_1, ANALOG_LOW);
	h_bridge_write(ENGINE_LEFT_2, ANALOG_LOW);

	current_engine_right = TT_ENGINE_DEFAULT;
	h_bridge_write(ENGINE_RIGHT_1, ANALOG_LOW);
	h_bridge_write(ENGINE_RIGHT_2, ANALOG_LOW);

	delayMicroseconds(256);
}
#endif

#if !defined MODERN_ELECTRONICS
static void init_legacy()
{
	set_standby(false);

	current_engine_left = TT_ENGINE_DEFAULT;
	digitalWrite(ENGINE_LEFT_1, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(ENGINE_LEFT_2, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(ENGINE_LEFT_PWM, current_engine_left.speed);

	current_engine_right = TT_ENGINE_DEFAULT;
	digitalWrite(ENGINE_RIGHT_1, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(ENGINE_RIGHT_2, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(ENGINE_RIGHT_PWM, current_engine_right.speed);
}
#endif

void init()
{
#if defined MODERN_ELECTRONICS
	init_modern();
#else
	init_legacy();
#endif
}

bool get_standby()
{
	return standby_mode;
}

#if defined MODERN_ELECTRONICS
static void set_standby_modern(const bool mode)
{
	standby_mode = mode;
}
#endif

#if !defined MODERN_ELECTRONICS
static void set_standby_legacy(const bool mode)
{
	standby_mode = mode;
	digitalWrite(ENGINE_STANDBY, static_cast<uint8_t>(!standby_mode));
}
#endif

void set_standby(const bool mode)
{
#if defined MODERN_ELECTRONICS
	set_standby_modern(mode);
#else
	set_standby_legacy(mode);
#endif
}

#if defined MODERN_ELECTRONICS
static void move_modern(const engine_t engine_left, const engine_t engine_right)
{
	h_bridge_write(ENGINE_LEFT_1, ANALOG_LOW);
	h_bridge_write(ENGINE_LEFT_2, ANALOG_LOW);
	h_bridge_write(ENGINE_RIGHT_1, ANALOG_LOW);
	h_bridge_write(ENGINE_RIGHT_2, ANALOG_LOW);
	delayMicroseconds(256);

	current_engine_left = engine_left;
	h_bridge_write(
	    ENGINE_LEFT_1,
	    current_engine_left.speed * (current_engine_left.sense == TT_ENGINE_SENSE_BACK)
	);
	h_bridge_write(
	    ENGINE_LEFT_2,
	    current_engine_left.speed * (current_engine_left.sense == TT_ENGINE_SENSE_FRONT)
	);

	current_engine_right = engine_right;
	h_bridge_write(
	    ENGINE_RIGHT_1,
	    current_engine_right.speed * (current_engine_right.sense == TT_ENGINE_SENSE_BACK)
	);
	h_bridge_write(
	    ENGINE_RIGHT_2,
	    current_engine_right.speed * (current_engine_right.sense == TT_ENGINE_SENSE_FRONT)
	);
}
#endif

#if !defined MODERN_ELECTRONICS
static void move_legacy(const engine_t engine_left, const engine_t engine_right)
{
	if (current_engine_left == engine_left && current_engine_right == engine_right)
	{
		return;
	}

	current_engine_left = engine_left;
	digitalWrite(ENGINE_LEFT_1, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(ENGINE_LEFT_2, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(ENGINE_LEFT_PWM, current_engine_left.speed);

	current_engine_right = engine_right;
	digitalWrite(ENGINE_RIGHT_1, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(ENGINE_RIGHT_2, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(ENGINE_RIGHT_PWM, current_engine_right.speed);
}
#endif

void move(const engine_t engine_left, const engine_t engine_right)
{
#if defined MODERN_ELECTRONICS
	move_modern(engine_left, engine_right);
#else
	move_legacy(engine_left, engine_right);
#endif
}

#if defined MODERN_ELECTRONICS
static void stop_modern(const uint8_t force)
{
	current_engine_left = TT_ENGINE_FRONT_STOP;
	current_engine_right = TT_ENGINE_FRONT_STOP;

	h_bridge_write(ENGINE_LEFT_1, ANALOG_LOW);
	h_bridge_write(ENGINE_LEFT_2, ANALOG_LOW);
	h_bridge_write(ENGINE_RIGHT_1, ANALOG_LOW);
	h_bridge_write(ENGINE_RIGHT_2, ANALOG_LOW);
	delayMicroseconds(256);

	h_bridge_write(ENGINE_LEFT_1, force);
	h_bridge_write(ENGINE_LEFT_2, force);
	h_bridge_write(ENGINE_RIGHT_1, force);
	h_bridge_write(ENGINE_RIGHT_2, force);
	delayMicroseconds(128);
}
#endif

#if !defined MODERN_ELECTRONICS
static void stop_legacy(const uint8_t force)
{
	current_engine_left = TT_ENGINE_FRONT_STOP;
	digitalWrite(ENGINE_LEFT_1, HIGH);
	digitalWrite(ENGINE_LEFT_2, HIGH);
	analogWrite(ENGINE_LEFT_PWM, force);

	current_engine_right = TT_ENGINE_FRONT_STOP;
	digitalWrite(ENGINE_RIGHT_1, HIGH);
	digitalWrite(ENGINE_RIGHT_2, HIGH);
	analogWrite(ENGINE_RIGHT_PWM, force);
}
#endif

void stop(const uint8_t force)
{
#if defined MODERN_ELECTRONICS
	stop_modern(force);
#else
	stop_legacy(force);
#endif
}

void brake()
{
	stop(ANALOG_HIGH);
}

void loose()
{
	stop(ANALOG_LOW);
}

void debug(char *out_buffer, const size_t out_size, const engine_t engine, const char *msg)
{
	snprintf(
	    out_buffer,
	    out_size - 1,
	    "\"%s\" = { direction:%i; speed:%i }\n",
	    msg,
	    engine.sense,
	    engine.speed
	);
}

void debug(const engine_t engine, const char *msg)
{
	char buffer[BUFFER_SIZE];
	debug(buffer, BUFFER_SIZE, engine, msg);
	Serial.print(buffer);
}
} // namespace tt::engine
