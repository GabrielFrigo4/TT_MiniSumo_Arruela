#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wcpp"
#include <Arduino.h>
#pragma GCC diagnostic pop
#include "utilitie.hpp"
#include "engine.hpp"

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

#pragma region "Engine Macros"
#define PIN_BOOL(x) ((HIGH) * (x) + (LOW) * !(x))
#pragma endregion "Engine Macros"

namespace tt::engine
{
	engine_t current_engine_left = TT_ENGINE_DEFAULT;
	engine_t current_engine_right = TT_ENGINE_DEFAULT;
	bool standby_mode = true;

	void setup()
	{
		pinMode(A_1, OUTPUT);
		pinMode(A_2, OUTPUT);
		pinMode(B_1, OUTPUT);
		pinMode(B_2, OUTPUT);
	}

	void init()
	{
		current_engine_left = TT_ENGINE_DEFAULT;
		analogWrite(A_1, ANALOG_LOW);
		analogWrite(A_2, ANALOG_LOW);

		current_engine_right = TT_ENGINE_DEFAULT;
		analogWrite(B_1, ANALOG_LOW);
		analogWrite(B_2, ANALOG_LOW);

		delayMicroseconds(512);
	}

	void move(const engine_t engine_left, const engine_t engine_right)
	{
		analogWrite(A_1, ANALOG_LOW);
		analogWrite(A_2, ANALOG_LOW);
		analogWrite(B_1, ANALOG_LOW);
		analogWrite(B_2, ANALOG_LOW);
		delayMicroseconds(512);

		current_engine_left = engine_left;
		analogWrite(A_1, current_engine_left.speed * (current_engine_left.direction == TT_ENGINE_DIRECTION_BACK));
		analogWrite(A_2, current_engine_left.speed * (current_engine_left.direction == TT_ENGINE_DIRECTION_FRONT));

		current_engine_right = engine_right;
		analogWrite(B_1, current_engine_right.speed * (current_engine_right.direction == TT_ENGINE_DIRECTION_BACK));
		analogWrite(B_2, current_engine_right.speed * (current_engine_right.direction == TT_ENGINE_DIRECTION_FRONT));
	}

	void stop()
	{
		analogWrite(A_1, ANALOG_LOW);
		analogWrite(A_2, ANALOG_LOW);
		analogWrite(B_1, ANALOG_LOW);
		analogWrite(B_2, ANALOG_LOW);
		delayMicroseconds(512);

		analogWrite(A_1, ANALOG_HIGH);
		analogWrite(A_2, ANALOG_HIGH);
		analogWrite(B_1, ANALOG_HIGH);
		analogWrite(B_2, ANALOG_HIGH);
		delayMicroseconds(256);

		current_engine_left = TT_ENGINE_FRONT_STOP;
		current_engine_right = TT_ENGINE_FRONT_STOP;
	}

	void debug(char *out_buffer, const size_t out_size, engine_t engine, const char *msg)
	{
		snprintf(
			out_buffer, out_size - 1,
			"\"%s\" = { direction:%i; speed:%i }\n",
			msg, engine.direction, engine.speed);
	}

	void debug(engine_t engine, const char *msg)
	{
		char buffer[BUFFER_SIZE];
		debug(buffer, BUFFER_SIZE, engine, msg);
		Serial.print(buffer);
	}
}
