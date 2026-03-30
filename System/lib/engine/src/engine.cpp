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
#error "[ERROR]: BUFFER_SIZE must be defined before compilation!"
#endif
#pragma endregion "Size Data Defines"

#pragma region "Analog Data Defines"
#ifndef ANALOG_LOW
#define ANALOG_LOW 0
#endif
#ifndef ANALOG_HIGH
#define ANALOG_HIGH 255
#endif
#pragma endregion "Analog Data Defines"

#pragma region "Engine Pinning Macros"
#ifndef A_1
#error "[ERROR]: A_1 must be defined before compilation!"
#endif
#ifndef A_2
#error "[ERROR]: A_2 must be defined before compilation!"
#endif
#ifndef B_1
#error "[ERROR]: B_1 must be defined before compilation!"
#endif
#ifndef B_2
#error "[ERROR]: B_2 must be defined before compilation!"
#endif
#pragma endregion "Engine Pinning Macros"

#pragma region "Engine Legacy Pinning Macros"
#ifndef PWM_A
#error "[ERROR]: PWM_A must be defined before compilation!"
#endif
#ifndef PWM_B
#error "[ERROR]: PWM_B must be defined before compilation!"
#endif
#ifndef STBY
#error "[ERROR]: STBY must be defined before compilation!"
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

bool get_standby()
{
	return standby_mode;
}

void set_standby(const bool mode)
{
	standby_mode = mode;
	digitalWrite(STBY, static_cast<uint8_t>(!standby_mode));
}

void setup()
{
	/*
	pinMode(A_1, OUTPUT);
	pinMode(A_2, OUTPUT);
	pinMode(B_1, OUTPUT);
	pinMode(B_2, OUTPUT);
	*/

	pinMode(PWM_A, OUTPUT);
	pinMode(A_1, OUTPUT);
	pinMode(A_2, OUTPUT);
	pinMode(PWM_B, OUTPUT);
	pinMode(B_1, OUTPUT);
	pinMode(B_2, OUTPUT);
	pinMode(STBY, OUTPUT);
	set_standby(true);
}

void init()
{
	/*
	current_engine_left = TT_ENGINE_DEFAULT;
	analogWrite(A_1, ANALOG_LOW);
	analogWrite(A_2, ANALOG_LOW);

	current_engine_right = TT_ENGINE_DEFAULT;
	analogWrite(B_1, ANALOG_LOW);
	analogWrite(B_2, ANALOG_LOW);

	delayMicroseconds(256);
	*/

	set_standby(false);

	current_engine_left = TT_ENGINE_DEFAULT;
	digitalWrite(A_1, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(A_2, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(PWM_A, current_engine_left.speed);

	current_engine_right = TT_ENGINE_DEFAULT;
	digitalWrite(B_1, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(B_2, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(PWM_B, current_engine_right.speed);
}

void move(const engine_t engine_left, const engine_t engine_right)
{
	/*
	analogWrite(A_1, ANALOG_LOW);
	analogWrite(A_2, ANALOG_LOW);
	analogWrite(B_1, ANALOG_LOW);
	analogWrite(B_2, ANALOG_LOW);
	delayMicroseconds(256);

	current_engine_left = engine_left;
	analogWrite(A_1, current_engine_left.speed * (current_engine_left.sense ==
	TT_ENGINE_SENSE_BACK)); analogWrite(A_2, current_engine_left.speed *
	(current_engine_left.sense == TT_ENGINE_SENSE_FRONT));

	current_engine_right = engine_right;
	analogWrite(B_1, current_engine_right.speed * (current_engine_right.sense ==
	TT_ENGINE_SENSE_BACK)); analogWrite(B_2, current_engine_right.speed *
	(current_engine_right.sense == TT_ENGINE_SENSE_FRONT));
	*/

	if (current_engine_left == engine_left && current_engine_right == engine_right)
	{
		return;
	}

	current_engine_left = engine_left;
	digitalWrite(A_1, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(A_2, PIN_BOOL(current_engine_left.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(PWM_A, current_engine_left.speed);

	current_engine_right = engine_right;
	digitalWrite(B_1, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_BACK));
	digitalWrite(B_2, PIN_BOOL(current_engine_right.sense == TT_ENGINE_SENSE_FRONT));
	analogWrite(PWM_B, current_engine_right.speed);
}

void stop(const uint8_t force)
{
	/*
	analogWrite(A_1, ANALOG_LOW);
	analogWrite(A_2, ANALOG_LOW);
	analogWrite(B_1, ANALOG_LOW);
	analogWrite(B_2, ANALOG_LOW);
	delayMicroseconds(256);

	analogWrite(A_1, force);
	analogWrite(A_2, force);
	analogWrite(B_1, force);
	analogWrite(B_2, force);
	delayMicroseconds(128);

	current_engine_left = TT_ENGINE_FRONT_STOP;
	current_engine_right = TT_ENGINE_FRONT_STOP;
	*/

	analogWrite(PWM_A, force);
	analogWrite(PWM_B, force);

	digitalWrite(A_1, HIGH);
	digitalWrite(A_2, HIGH);
	digitalWrite(B_1, HIGH);
	digitalWrite(B_2, HIGH);

	current_engine_left = TT_ENGINE_FRONT_STOP;
	current_engine_right = TT_ENGINE_FRONT_STOP;
}

void brake()
{
	stop(255);
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
