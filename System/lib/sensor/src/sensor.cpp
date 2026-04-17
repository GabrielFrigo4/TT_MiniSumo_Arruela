#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wvla"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wcpp"
#include <Arduino.h>
#include <VL53L0X.h>
#include <Wire.h>
#pragma GCC diagnostic pop
#include "engine.hpp"
#include "internal.hpp"
#include "sensor.hpp"

#pragma region "Size Data Defines"
#ifndef BUFFER_SIZE
#error "[ERRO]: BUFFER_SIZE must be defined before compilation!"
#endif
#pragma endregion "Size Data Defines"

#pragma region "String Macros"
#ifndef STRLN
#define STRLN(x) x "\n"
#endif
#pragma endregion "String Macros"

#pragma region "Sensor Pinning Macros"
#ifndef SENSOR_TRANSISTOR
#error "[ERRO]: SENSOR_TRANSISTOR must be defined before compilation!"
#endif
#ifndef SENDER_LEFT
#error "[ERRO]: SENDER_LEFT must be defined before compilation!"
#endif
#ifndef SENDER_FRONT
#error "[ERRO]: SENDER_FRONT must be defined before compilation!"
#endif
#ifndef SENDER_RIGHT
#error "[ERRO]: SENDER_RIGHT must be defined before compilation!"
#endif
#ifndef RECEIVER_LEFT
#error "[ERRO]: RECEIVER_LEFT must be defined before compilation!"
#endif
#ifndef RECEIVER_RIGHT
#error "[ERRO]: RECEIVER_RIGHT must be defined before compilation!"
#endif
#ifndef SENSOR_LINE
#error "[ERRO]: SENSOR_LINE must be defined before compilation!"
#endif
#ifndef SENSOR_DATA
#error "[ERRO]: SENSOR_DATA must be defined before compilation!"
#endif
#ifndef SENSOR_CLOCK
#error "[ERRO]: SENSOR_CLOCK must be defined before compilation!"
#endif
#pragma endregion "Sensor Pinning Macros"

namespace tt::sensor
{
sensor_mode_t sensor_mode = sensor_mode_t::none;
VL53L0X sensor_dist;

static const char *mode_to_string(sensor_mode_t mode)
{
	static const char *const mode_strings[] = {
	    "sender",
	    "receiver",
	    "none",
	};

	if (mode <= sensor_mode_t::none)
	{
		return mode_strings[mode];
	}

	return "unknown";
}

void setup()
{
	pinMode(SENSOR_TRANSISTOR, OUTPUT);
	pinMode(SENDER_LEFT, INPUT);
	pinMode(SENDER_FRONT, INPUT);
	pinMode(SENDER_RIGHT, INPUT);
	pinMode(RECEIVER_LEFT, INPUT);
	pinMode(RECEIVER_RIGHT, INPUT);
	//pinMode(SENSOR_LINE, INPUT_PULLUP);

	/*
	Wire.begin(SENSOR_DATA, SENSOR_CLOCK);
	if (sensor_dist.init())
	{
		Serial.printf(STRLN("[INFO]: VL53L0X Init"));
		sensor_dist.startContinuous();
		Serial.printf(STRLN("[INFO]: VL53L0X Start Continuous"));
	}
	else
	{
		Serial.printf(STRLN("[ERRO]: VL53L0X don't Init"));
	}
	*/
}

void init()
{
	set_mode(sensor_mode_t::sender);
}

sensor_t create_snapshot()
{
	sensor_t sensor;
	sensor.mode = sensor_mode;
	switch (sensor_mode)
	{
	case sensor_mode_t::sender:
		sensor.left = digitalRead(SENDER_LEFT);
		sensor.front = digitalRead(SENDER_FRONT);
		sensor.right = digitalRead(SENDER_RIGHT);
		break;

	case sensor_mode_t::receiver:
		sensor.left = !digitalRead(RECEIVER_LEFT);
		sensor.right = !digitalRead(RECEIVER_RIGHT);
		sensor.front = sensor.left || sensor.right;
		break;

	case sensor_mode_t::none:
		break;
	}
	sensor.dist = -1;
	//sensor.dist = sensor_dist.readRangeContinuousMillimeters();
	sensor.line = -1;
	//sensor.line = digitalRead(SENSOR_LINE);
	return sensor;
}

sensor_mode_t get_mode()
{
	return sensor_mode;
}

void set_mode(sensor_mode_t mode)
{
	sensor_mode = mode;
	switch (sensor_mode)
	{
	case sensor_mode_t::sender:
		digitalWrite(SENSOR_TRANSISTOR, HIGH);
		break;

	case sensor_mode_t::receiver:
		digitalWrite(SENSOR_TRANSISTOR, LOW);
		break;

	case sensor_mode_t::none:
		break;
	}
}

void debug(char *out_buffer, const size_t out_size, const sensor_t sensor, const char *msg)
{
	snprintf(
	    out_buffer,
	    out_size - 1,
	    "\"%s\" = { mode:\"%s\"; left:%i; front:%i; right:%i; dist:%i; line:%i }\n",
	    msg,
	    mode_to_string(sensor.mode),
	    sensor.left,
	    sensor.front,
	    sensor.right,
	    sensor.dist,
	    sensor.line
	);
}

void debug(const sensor_t sensor, const char *msg)
{
	char buffer[BUFFER_SIZE];
	debug(buffer, BUFFER_SIZE, sensor, msg);
	Serial.print(buffer);
}
} // namespace tt::sensor
