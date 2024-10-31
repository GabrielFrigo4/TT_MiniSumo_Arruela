#include <Arduino.h>
#include <ps4.h>
#include <PS4Controller.h>
#include <ps4_int.h>
#include "controller.hpp"

namespace tt::controller
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

	controller_t create_snapshot()
	{
		controller_t controller;

		controller.right = PS4.Right();
		controller.down = PS4.Down();
		controller.up = PS4.Up();
		controller.left = PS4.Left();

		controller.upright = PS4.UpRight();
		controller.downright = PS4.DownRight();
		controller.upleft = PS4.UpLeft();
		controller.downleft = PS4.DownLeft();

		controller.square = PS4.Square();
		controller.cross = PS4.Cross();
		controller.circle = PS4.Circle();
		controller.triangle = PS4.Triangle();

		controller.r2 = PS4.R2();
		controller.l2 = PS4.L2();

		controller.r2_value = PS4.R2Value();
		controller.l2_value = PS4.L2Value();

		controller.r_stick_x = PS4.RStickX();
		controller.r_stick_y = PS4.RStickY();
		controller.l_stick_x = PS4.LStickX();
		controller.l_stick_y = PS4.LStickY();

		return controller;
	}

	void debug(char *out_buffer, const size_t out_size, const controller_t controller, const char *msg)
	{
		snprintf(out_buffer, out_size, "\"%s\" = { R2:%i; R2_Value:%i; L2:%i; L2_Value:%i; Square:%i; Cross:%i; Circle:%i; Triangle:%i; RStickX:%i; RStickY:%i; LStickX:%i; LStickY:%i }\n",
				 msg, controller.r2, controller.r2_value, controller.l2, controller.l2_value,
				 controller.square, controller.cross, controller.circle, controller.triangle,
				 controller.r_stick_x, controller.r_stick_y, controller.l_stick_x, controller.l_stick_y);
	}

	void debug(const controller_t controller, const char *msg)
	{
		const size_t buffer_len = 512;
		char buffer[buffer_len];
		debug(buffer, buffer_len, controller, msg);
		Serial.print(buffer);
	}
}