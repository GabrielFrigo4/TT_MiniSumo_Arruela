#include <Arduino.h>
#include <dualshock4.hpp>
#include <engine.hpp>
#include <internal.hpp>
#include <utilities.hpp>
#include "kernel-rc.hpp"

namespace tt::kernel_rc
{
#pragma region "Types"
	enum direction_t
	{
		left,
		right,
	};
#pragma endregion "Types"

#pragma region "Signatures"
	void update_controller();
	void update_engine();
	void reset_engine();
	void behavior_escape(const uint8_t sense);
	void behavior_forward(const uint8_t sense, const uint8_t speed_modifier, const uint8_t sense_modifier);
	void behavior_curve(const uint8_t left_sense, const uint8_t righ_sense);
	void behavior_accelerated_go();
	void behavior_just_go();
	void macro_curvinha(const direction_t left_sense);
	void macro_curvao(const direction_t left_sense);
	void macro_ladinho(const direction_t left_sense);
	void special_diagonal();
#pragma endregion "Signatures"

#pragma region "Engine Data"
	tt::engine_t engine_left = TT_ENGINE_DEFAULT;
	tt::engine_t engine_right = TT_ENGINE_DEFAULT;
#pragma endregion "Engine Data"

#pragma region "Controller Data"
	tt::dualshock4_t controller;
	uint8_t rc_state = RC_STATE_CAREFUL;
	bool triangle = false;
#pragma endregion "Controller Data"

#pragma region "Main Functions"
	void setup()
	{
		tt::internal::setup();
		tt::internal::set_led(false);
		Serial.printf(STRLN("Setup Internal!"));
		Serial.printf(STRLN("Mac Address: %s"), tt::internal::mac_address());
		vTaskDelay(512);

		tt::dualshock4::setup(tt::internal::mac_address());
		Serial.printf(STRLN("Setup DualShock4!"));

		tt::engine::setup();
		Serial.printf(STRLN("Setup Engine!"));
	}

	void init()
	{
		tt::engine::init();
	}

	void update()
	{
		tt::internal::set_led(true);
		if (tt::dualshock4::disconnected())
		{
			tt::internal::set_led(false);
			reset_engine();
			return;
		}

		special_diagonal();
		update_controller();

		if (controller.l1)
		{
			Serial.printf(STRLN("(controller.l1)"));
			macro_ladinho(left);
			return;
		}

		if (controller.r1)
		{
			Serial.printf(STRLN("(controller.r1)"));
			macro_ladinho(right);
			return;
		}

		if (controller.square)
		{
			Serial.printf(STRLN("(controller.square)"));
			macro_curvinha(left);
			return;
		}

		if (controller.circle)
		{
			Serial.printf(STRLN("(controller.circle)"));
			macro_curvinha(right);
			return;
		}

		if (controller.left)
		{
			Serial.printf(STRLN("(controller.left)"));
			macro_curvao(left);
			return;
		}

		if (controller.right)
		{
			Serial.printf(STRLN("(controller.right)"));
			macro_curvao(right);
			return;
		}

		if (controller.up)
		{
			Serial.printf(STRLN("(controller.up)"));
			behavior_accelerated_go();
			update_engine();
			return;
		}

		if (controller.down)
		{
			Serial.printf(STRLN("(controller.down)"));
			behavior_escape(TT_ENGINE_SENSE_BACK);
			update_engine();
			return;
		}

		if (controller.cross)
		{
			Serial.printf(STRLN("(controller.cross)"));
			behavior_just_go();
			update_engine();
			return;
		}

		if (controller.r2 && controller.r2_value >= BUTTON_TRIGGER)
		{
			Serial.printf(STRLN("(controller.r2)"));
			behavior_forward(TT_ENGINE_SENSE_FRONT, controller.r2_value, tt::utilities::abs(controller.l_stick_x));
			update_engine();
			return;
		}

		if (controller.l2 && controller.l2_value >= BUTTON_TRIGGER)
		{
			Serial.printf(STRLN("(controller.l2)"));
			behavior_forward(TT_ENGINE_SENSE_BACK, controller.l2_value * 0.9, tt::utilities::abs(controller.l_stick_x * 0.9));
			update_engine();
			return;
		}

		if (controller.l_stick_x <= -STICK_TRIGGER)
		{
			Serial.printf(STRLN("(controller.l_stick_x <= -STICK_TRIGGER)"));
			behavior_curve(TT_ENGINE_SENSE_BACK, TT_ENGINE_SENSE_FRONT);
			update_engine();
			return;
		}

		if (controller.l_stick_x >= STICK_TRIGGER)
		{
			Serial.printf(STRLN("(controller.l_stick_x >= STICK_TRIGGER)"));
			behavior_curve(TT_ENGINE_SENSE_FRONT, TT_ENGINE_SENSE_BACK);
			update_engine();
			return;
		}

		reset_engine();
	}
#pragma endregion "Main Functions"

#pragma region "Controller Functions"
	void update_controller()
	{
		controller = tt::dualshock4::create_snapshot();
		if (controller.triangle)
		{
			Serial.printf(STRLN("(controller.triangle)"));
			if (!triangle)
			{
				switch (rc_state)
				{
				case RC_STATE_CAREFUL:
					rc_state = RC_STATE_NORMAL;
					break;

				case RC_STATE_NORMAL:
					rc_state = RC_STATE_CAREFUL;
					break;

				default:
					rc_state = RC_STATE_CAREFUL;
					break;
				}
			}
			triangle = true;
		}
		else
		{
			triangle = false;
		}
	}
#pragma endregion "Controller Functions"

#pragma region "Engine Functions"
	void update_engine()
	{
		Serial.printf("################################################################################################################################\n");
		tt::engine::debug(engine_left, "engine_left");
		tt::engine::debug(engine_right, "engine_right");
		tt::dualshock4::debug(controller, "controller");
		tt::internal::debug("internal");
		tt::engine::move(engine_left, engine_right);
		vTaskDelay(1);
	}

	void reset_engine()
	{
		engine_left = TT_ENGINE_FRONT_STOP;
		engine_right = TT_ENGINE_FRONT_STOP;
		switch (rc_state)
		{
		case RC_STATE_CAREFUL:
			tt::engine::stop();
			break;

		case RC_STATE_NORMAL:
			tt::engine::move(engine_left, engine_right);
			break;

		default:
			break;
		}
		tt::internal::setup_millis();
		vTaskDelay(1);
	}
#pragma endregion "Engine Functions"

#pragma region "Behavior Functions"
	void behavior_escape(const uint8_t sense)
	{
		const uint8_t base_speed = TT_ENGINE_SPEED_FULL;
		engine_left = {sense, base_speed};
		engine_right = {sense, base_speed};

		if (controller.l_stick_x <= -STICK_TRIGGER)
		{
			engine_left.speed >>= 3;
		}
		else if (controller.l_stick_x >= STICK_TRIGGER)
		{
			engine_right.speed >>= 3;
		}
	}

	void behavior_forward(const uint8_t sense, const uint8_t speed_modifier, const uint8_t sense_modifier)
	{
		const uint8_t min_v = speed_modifier >> 3;
		const uint8_t max_v = speed_modifier;
		const uint8_t base_speed = static_cast<uint8_t>(
			TT_INTERNAL_BETWEEN(tt::internal::delta_millis() + min_v, min_v, max_v));

		switch (rc_state)
		{
		case RC_STATE_CAREFUL:
			engine_left = {sense, static_cast<uint8_t>(base_speed - (base_speed >> 3))};
			engine_right = {sense, static_cast<uint8_t>(base_speed - (base_speed >> 3))};
			break;

		case RC_STATE_NORMAL:
			engine_left = {sense, static_cast<uint8_t>(base_speed - (base_speed >> 3))};
			engine_right = {sense, static_cast<uint8_t>(base_speed - (base_speed >> 3))};
			// engine_left = {sense, base_speed};
			// engine_right = {sense, base_speed};
			break;

		default:
			break;
		}

		direction_t direction = (controller.l_stick_x < 0 ? direction_t::left : direction_t::right);
		switch (direction)
		{
		case direction_t::left:
			engine_left.speed -= sense_modifier * (engine_left.speed / 127.0f);
			break;
		
		case direction_t::right:
			engine_right.speed -= sense_modifier * (engine_right.speed / 127.0f);
			break;
		}
	}

	void behavior_curve(const uint8_t left_sense, const uint8_t righ_sense)
	{
		const uint8_t min_v = TT_ENGINE_SPEED_SHIFT(3);
		const uint8_t max_v = TT_ENGINE_SPEED_SHIFT(2);
		const uint8_t base_speed = static_cast<uint8_t>(
			TT_INTERNAL_BETWEEN((tt::internal::delta_millis() / 3) * 2 + min_v, min_v, max_v));

		switch (rc_state)
		{
		case RC_STATE_CAREFUL:
			engine_left.speed = static_cast<uint8_t>(base_speed + 4);
			engine_right.speed = static_cast<uint8_t>(base_speed + 4);
			break;

		case RC_STATE_NORMAL:
			engine_left.speed = static_cast<uint8_t>(base_speed + 4);
			engine_right.speed = static_cast<uint8_t>(base_speed + 4);
			// engine_left.speed = static_cast<uint8_t>(base_speed + 24);
			// engine_right.speed = static_cast<uint8_t>(base_speed + 24);
			break;

		default:
			break;
		}
		engine_left.sense = left_sense;
		engine_right.sense = righ_sense;
	}

	void behavior_accelerated_go()
	{
		const uint8_t min_v = TT_ENGINE_SPEED_SHIFT(3);
		const uint8_t max_v = TT_ENGINE_SPEED_FULL;
		const uint8_t base_speed = static_cast<uint8_t>(
			TT_INTERNAL_BETWEEN(tt::internal::delta_millis() + min_v, min_v, max_v));
		engine_left = {TT_ENGINE_SENSE_FRONT, base_speed};
		engine_right = {TT_ENGINE_SENSE_FRONT, base_speed};
	}

	void behavior_just_go()
	{
		engine_left = TT_ENGINE_FRONT_FULL;
		engine_right = TT_ENGINE_FRONT_FULL;
	}
#pragma endregion "Behavior Functions"

#pragma region "Macro Functions"
	void macro_curvinha(const direction_t direction)
	{
		switch (direction)
		{
		case direction_t::left:
			tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
			vTaskDelay(72);
			tt::engine::move(TT_ENGINE_FRONT(255), TT_ENGINE_FRONT(64));
			vTaskDelay(245);
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
			vTaskDelay(72);
			break;

		case direction_t::right:
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
			vTaskDelay(72);
			tt::engine::move(TT_ENGINE_FRONT(64), TT_ENGINE_FRONT(255));
			vTaskDelay(245);
			tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
			vTaskDelay(72);
			break;
		}
	}

	void macro_curvao(const direction_t direction)
	{
		switch (direction)
		{
		case direction_t::left:
			tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
			vTaskDelay(72);
			tt::engine::move(TT_ENGINE_FRONT(255), TT_ENGINE_FRONT(48));
			vTaskDelay(392);
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
			vTaskDelay(72);
			break;

		case direction_t::right:
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
			vTaskDelay(72);
			tt::engine::move(TT_ENGINE_FRONT(48), TT_ENGINE_FRONT(255));
			vTaskDelay(392);
			tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
			vTaskDelay(72);
			break;
		}
	}

	void macro_ladinho(const direction_t direction)
	{
		switch (direction)
		{
		case direction_t::left:
			tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
			vTaskDelay(72);
			tt::engine::move(TT_ENGINE_FRONT(255), TT_ENGINE_FRONT(24));
			vTaskDelay(224);
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
			vTaskDelay(72);
			break;

		case direction_t::right:
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
			vTaskDelay(72);
			tt::engine::move(TT_ENGINE_FRONT(24), TT_ENGINE_FRONT(255));
			vTaskDelay(224);
			tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
			vTaskDelay(72);
			break;
		}
	}
#pragma endregion "Macro Functions"

#pragma region "Special Functions"
	void special_diagonal()
	{
		update_controller();
		if (tt::utilities::abs(controller.r_stick_x) > STICK_TRIGGER)
		{
			direction_t direction = (controller.r_stick_x < 0 ? direction_t::left : direction_t::right);
			switch (direction)
			{
			case direction_t::left:
				tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
				vTaskDelay(32);
				break;

			case direction_t::right:
				tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
				vTaskDelay(32);
				break;
			}
		}
		while (tt::utilities::abs(controller.r_stick_x) > STICK_TRIGGER)
		{
			update_controller();
			tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_FRONT_FULL);
		}
	}
#pragma endregion "Special Functions"
}
