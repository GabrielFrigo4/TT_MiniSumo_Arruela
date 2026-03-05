#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wcpp"
#include <Arduino.h>
#pragma GCC diagnostic pop
#include "sensor.hpp"
#include "engine.hpp"
#include "internal.hpp"

#pragma region "Size Data Defines"
#ifndef BUFFER_SIZE
#error "[ERROR]: BUFFER_SIZE must be defined before compilation!"
#endif
#pragma endregion "Size Data Defines"

#pragma region "Sensor Pinning Macros"
#ifndef SENSOR_TRANSISTOR
#error "[ERROR]: SENSOR_TRANSISTOR must be defined before compilation!"
#endif
#ifndef SENSOR_LEFT
#error "[ERROR]: SENSOR_LEFT must be defined before compilation!"
#endif
#ifndef SENSOR_FRONT
#error "[ERROR]: SENSOR_FRONT must be defined before compilation!"
#endif
#ifndef SENSOR_RIGHT
#error "[ERROR]: SENSOR_RIGHT must be defined before compilation!"
#endif
#ifndef RECEIVER_LEFT
#error "[ERROR]: RECEIVER_LEFT must be defined before compilation!"
#endif
#ifndef RECEIVER_FRONT
#error "[ERROR]: RECEIVER_FRONT must be defined before compilation!"
#endif
#ifndef RECEIVER_RIGHT
#error "[ERROR]: RECEIVER_RIGHT must be defined before compilation!"
#endif
#pragma endregion "Sensor Pinning Macros"

namespace tt::sensor
{
	sensor_mode_t sensor_mode = sensor_mode_t::none;

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
		pinMode(SENSOR_LEFT, INPUT);
		pinMode(SENSOR_FRONT, INPUT);
		pinMode(SENSOR_RIGHT, INPUT);
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
			sensor.left = digitalRead(SENSOR_LEFT);
			sensor.front = digitalRead(SENSOR_FRONT);
			sensor.right = digitalRead(SENSOR_RIGHT);
			break;
		case sensor_mode_t::receiver:
			sensor.left = !digitalRead(RECEIVER_LEFT);
			sensor.front = !digitalRead(RECEIVER_FRONT);
			sensor.right = !digitalRead(RECEIVER_RIGHT);
			break;
		case sensor_mode_t::none:
			break;
		}
		return sensor;
	}

	sensor_mode_t get_mode()
	{
		return sensor_mode;
	}

	void set_mode(sensor_mode_t mode)
	{
		switch (mode)
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
		sensor_mode = mode;
	}

	void debug(char *out_buffer, const size_t out_size, sensor_t sensor, const char *msg)
	{
		snprintf(
			out_buffer, out_size - 1,
			"\"%s\" = { left:%i; front:%i; right:%i; mode:\"%s\" }\n",
			msg, sensor.left, sensor.front, sensor.right,
			mode_to_string(sensor.mode));
	}

	void debug(sensor_t sensor, const char *msg)
	{
		char buffer[BUFFER_SIZE];
		debug(buffer, BUFFER_SIZE, sensor, msg);
		Serial.print(buffer);
	}
}
