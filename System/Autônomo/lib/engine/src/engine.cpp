#include <Arduino.h>
#include <utilitie.hpp>
#include "engine.hpp"

#pragma region "Size Data Defines"
#ifndef BYTE_SIZE
#define BYTE_SIZE 256
#endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE (BYTE_SIZE * 2)
#endif
#ifndef STACK_SIZE
#define STACK_SIZE (BYTE_SIZE * 16)
#endif
#pragma endregion "Size Data Defines"

#pragma region "Engine Pinning Macros"
#ifndef A_1
#define A_1 16
#endif
#ifndef A_2
#define A_2 17
#endif
#ifndef B_1
#define B_1 18
#endif
#ifndef B_2
#define B_2 19
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
		digitalWrite(A_1, LOW);
		digitalWrite(A_2, LOW);

		current_engine_right = TT_ENGINE_DEFAULT;
		digitalWrite(B_1, LOW);
		digitalWrite(B_2, LOW);
	}

	void move(const engine_t engine_left, const engine_t engine_right)
	{
		//if (current_engine_left == engine_left && current_engine_right == engine_right)
		//{
		//	return;
		//}

		digitalWrite(A_1, LOW);
		digitalWrite(A_2, LOW);
		digitalWrite(B_1, LOW);
		digitalWrite(B_2, LOW);
		delayMicroseconds(60);

		current_engine_left = engine_left;
		digitalWrite(A_1, current_engine_left.speed * (current_engine_left.direction == TT_ENGINE_DIRECTION_BACK));
		digitalWrite(A_2, current_engine_left.speed * (current_engine_left.direction == TT_ENGINE_DIRECTION_FRONT));

		current_engine_right = engine_right;
		digitalWrite(B_1, current_engine_right.speed * (current_engine_right.direction == TT_ENGINE_DIRECTION_BACK));
		digitalWrite(B_2, current_engine_right.speed * (current_engine_right.direction == TT_ENGINE_DIRECTION_FRONT));
	}

	void stop()
	{
		digitalWrite(A_1, HIGH);
		digitalWrite(A_2, HIGH);
		digitalWrite(B_1, HIGH);
		digitalWrite(B_2, HIGH);

		current_engine_left = TT_ENGINE_FRONT_STOP;
		current_engine_right = TT_ENGINE_FRONT_STOP;
	}

	void debug(char *out_buffer, const size_t out_size, engine_t engine, const char *msg)
	{
		snprintf(out_buffer, out_size - 1, "\"%s\" = { direction:%i; speed:%i }\n", msg, engine.direction, engine.speed);
	}

	void debug(engine_t engine, const char *msg)
	{
		char buffer[BUFFER_SIZE];
		debug(buffer, BUFFER_SIZE, engine, msg);
		Serial.print(buffer);
	}
}