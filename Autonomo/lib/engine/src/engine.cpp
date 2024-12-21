#include <Arduino.h>
#include "engine.hpp"

#pragma region "Engine Pinning Macros"
#define pwmA 4
#define a1 18
#define a2 19
#define pwmB 23
#define b1 16
#define b2 17
#define stby 5
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
		pinMode(pwmA, OUTPUT);
		pinMode(a1, OUTPUT);
		pinMode(a2, OUTPUT);
		pinMode(pwmB, OUTPUT);
		pinMode(b1, OUTPUT);
		pinMode(b2, OUTPUT);
		pinMode(stby, OUTPUT);
		set_standby(true);
	}

	bool get_standby()
	{
		return standby_mode;
	}

	void set_standby(const bool mode)
	{
		standby_mode = mode;
		digitalWrite(stby, static_cast<uint8_t>(!standby_mode));
	}

	void init()
	{
		set_standby(false);

		current_engine_left = TT_ENGINE_DEFAULT;
		digitalWrite(a1, PIN_BOOL(current_engine_left.direction == TT_ENGINE_DIRECTION_BACK));
		digitalWrite(a2, PIN_BOOL(current_engine_left.direction == TT_ENGINE_DIRECTION_FRONT));
		analogWrite(pwmA, current_engine_left.speed);

		current_engine_right = TT_ENGINE_DEFAULT;
		digitalWrite(b1, PIN_BOOL(current_engine_right.direction == TT_ENGINE_DIRECTION_BACK));
		digitalWrite(b2, PIN_BOOL(current_engine_right.direction == TT_ENGINE_DIRECTION_FRONT));
		analogWrite(pwmB, current_engine_right.speed);

	}

	void move(const engine_t engine_left, const engine_t engine_right)
	{
		if (current_engine_left == engine_left && current_engine_right == engine_right)
		{
			return;
		}

		current_engine_left = engine_left;
		uint8_t a1_v = PIN_BOOL(current_engine_left.direction == TT_ENGINE_DIRECTION_BACK);
		uint8_t a2_v = PIN_BOOL(current_engine_left.direction == TT_ENGINE_DIRECTION_FRONT);
	
		current_engine_right = engine_right;
		uint8_t b1_v = PIN_BOOL(current_engine_right.direction == TT_ENGINE_DIRECTION_BACK);
		uint8_t b2_v = PIN_BOOL(current_engine_right.direction == TT_ENGINE_DIRECTION_FRONT);

		if (engine_left.direction != engine_right.direction) {
			uint8_t tmp;
			
			tmp = a1_v;
			a1_v = a2_v;
			a2_v = a1_v;

			tmp = b1_v;
			b1_v = b2_v;
			b2_v = b1_v;
		}

		digitalWrite(a1, a1_v);
		digitalWrite(a2, a2_v);
		analogWrite(pwmA, current_engine_left.speed);

		digitalWrite(b1, b1_v);
		digitalWrite(b2, b2_v);
		analogWrite(pwmB, current_engine_right.speed);
	}

	void stop()
	{
		digitalWrite(a1, HIGH);
		digitalWrite(a2, HIGH);
		digitalWrite(b1, HIGH);
		digitalWrite(b2, HIGH);

		current_engine_left = TT_ENGINE_DEFAULT;
		current_engine_right = TT_ENGINE_DEFAULT;
	}

	void debug(char *out_buffer, const size_t out_size, engine_t engine, const char *msg)
	{
		snprintf(out_buffer, out_size - 1, "\"%s\" = { direction:%i; speed:%i }\n", msg, engine.direction, engine.speed);
	}

	void debug(engine_t engine, const char *msg)
	{
		const size_t buffer_len = 512;
		char buffer[buffer_len];
		debug(buffer, buffer_len, engine, msg);
		Serial.print(buffer);
	}
}