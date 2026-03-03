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
#ifndef SENSOR_FRONT
#error "[ERROR]: SENSOR_FRONT must be defined before compilation!"
#endif
#ifndef SENSOR_RIGHT
#error "[ERROR]: SENSOR_RIGHT must be defined before compilation!"
#endif
#ifndef SENSOR_LEFT
#error "[ERROR]: SENSOR_LEFT must be defined before compilation!"
#endif
#pragma endregion "Sensor Pinning Macros"

namespace tt::sensor
{
	void setup()
	{
		pinMode(SENSOR_LEFT, INPUT);
		pinMode(SENSOR_FRONT, INPUT);
		pinMode(SENSOR_RIGHT, INPUT);
	}

	sensor_t create_snapshot()
	{
		sensor_t sensor;
		sensor.left = digitalRead(SENSOR_LEFT);
		sensor.front = digitalRead(SENSOR_FRONT);
		sensor.right = digitalRead(SENSOR_RIGHT);
		return sensor;
	}

	void debug(char *out_buffer, const size_t out_size, sensor_t sensor, const char *msg)
	{
		snprintf(out_buffer, out_size - 1, "\"%s\" = { left:%i; front:%i; right:%i }\n", msg, sensor.left, sensor.front, sensor.right);
	}

	void debug(sensor_t sensor, const char *msg)
	{
		char buffer[BUFFER_SIZE];
		debug(buffer, BUFFER_SIZE, sensor, msg);
		Serial.print(buffer);
	}
}
