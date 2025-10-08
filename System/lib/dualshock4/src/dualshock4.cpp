#include <Arduino.h>
#include <ps4.h>
#include <PS4Controller.h>
#include <ps4_int.h>
#include "dualshock4.hpp"

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

namespace tt::dualshock4
{
	bool connected = false;

	void setup(const char *mac)
	{
		connected = PS4.begin(mac);
	}

	bool is_connected()
	{
		return PS4.isConnected();
	}

	bool disconnected()
	{
		return connected && !is_connected();
	}

	dualshock4_t create_snapshot()
	{
		dualshock4_t dualshock4;

		dualshock4.right = PS4.Right();
		dualshock4.down = PS4.Down();
		dualshock4.up = PS4.Up();
		dualshock4.left = PS4.Left();

		dualshock4.upright = PS4.UpRight();
		dualshock4.downright = PS4.DownRight();
		dualshock4.upleft = PS4.UpLeft();
		dualshock4.downleft = PS4.DownLeft();

		dualshock4.square = PS4.Square();
		dualshock4.cross = PS4.Cross();
		dualshock4.circle = PS4.Circle();
		dualshock4.triangle = PS4.Triangle();

		dualshock4.r1 = PS4.R1();
		dualshock4.l1 = PS4.L1();

		dualshock4.r2 = PS4.R2();
		dualshock4.l2 = PS4.L2();

		dualshock4.r2_value = PS4.R2Value();
		dualshock4.l2_value = PS4.L2Value();

		dualshock4.r_stick_x = PS4.RStickX();
		dualshock4.r_stick_y = PS4.RStickY();
		dualshock4.l_stick_x = PS4.LStickX();
		dualshock4.l_stick_y = PS4.LStickY();

		return dualshock4;
	}

	void debug(char *out_buffer, const size_t out_size, const dualshock4_t dualshock4, const char *msg)
	{
		snprintf(out_buffer, out_size, "\"%s\" = { R1:%i; L1:%i; R2:%i; R2_Value:%i; L2:%i; L2_Value:%i; Square:%i; Cross:%i; Circle:%i; Triangle:%i; RStickX:%i; RStickY:%i; LStickX:%i; LStickY:%i }\n",
				 msg, dualshock4.r1, dualshock4.l1, dualshock4.r2, dualshock4.r2_value, dualshock4.l2, dualshock4.l2_value,
				 dualshock4.square, dualshock4.cross, dualshock4.circle, dualshock4.triangle,
				 dualshock4.r_stick_x, dualshock4.r_stick_y, dualshock4.l_stick_x, dualshock4.l_stick_y);
	}

	void debug(const dualshock4_t dualshock4, const char *msg)
	{
		char buffer[BUFFER_SIZE];
		debug(buffer, BUFFER_SIZE, dualshock4, msg);
		Serial.print(buffer);
	}
}