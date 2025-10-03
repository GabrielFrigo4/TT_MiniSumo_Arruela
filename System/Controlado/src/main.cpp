#include <Arduino.h>
#include <controller.hpp>
#include <engine.hpp>
#include <internal.hpp>
#include "main.hpp"

#pragma region "Main State Data"
uint8_t loop_state = LOOP_STATE_INIT;
#pragma endregion "Main State Data"

#pragma region "Main Engine Data"
tt::engine_t engine_left = TT_ENGINE_DEFAULT;
tt::engine_t engine_right = TT_ENGINE_DEFAULT;
#pragma endregion "Main Engine Data"

#pragma region "Main Controller Data"
tt::controller_t controller;
uint8_t rc_state = RC_STATE_CAREFUL;
bool triangle = false;
#pragma endregion "Main Controller Data"

#pragma region "Main Data"
void setup()
{
	Serial.begin(115200);
	Serial.printf(STRLN("Serial 115200!"));

	tt::internal::setup();
	tt::internal::set_led(false);
	Serial.printf(STRLN("Setup Internal!"));
	Serial.printf(STRLN("Mac Address: %s"), tt::internal::mac_address());
	vTaskDelay(512);

	tt::controller::setup(tt::internal::mac_address());
	Serial.printf(STRLN("Setup Controller!"));

	tt::engine::setup();
	Serial.printf(STRLN("Setup Engine!"));
}
#pragma endregion "Main Setup"

#pragma region "Main Loop"
void __init__()
{
	tt::engine::init();
}

void __update__()
{
	tt::internal::set_led(true);
	if (tt::controller::disconnected())
	{
		tt::internal::set_led(false);
		reset_engine();
		return;
	}

	controller = tt::controller::create_snapshot();

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
		behavior_just_go();
		update_engine();
		return;
	}

	if (controller.down)
	{
		Serial.printf(STRLN("(controller.down)"));
		behavior_escape(TT_ENGINE_DIRECTION_BACK);
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

	if (controller.r2)
	{
		Serial.printf(STRLN("(controller.r2)"));
		behavior_forward(TT_ENGINE_DIRECTION_FRONT, controller.r2_value);
		update_engine();
		return;
	}

	if (controller.l2)
	{
		Serial.printf(STRLN("(controller.l2)"));
		behavior_forward(TT_ENGINE_DIRECTION_BACK, controller.l2_value * 0.9);
		update_engine();
		return;
	}

	if (controller.l_stick_x <= -STICK_TRIGGER)
	{
		Serial.printf(STRLN("(controller.l_stick_x <= -STICK_TRIGGER)"));
		behavior_curve(TT_ENGINE_DIRECTION_BACK, TT_ENGINE_DIRECTION_FRONT);
		update_engine();
		return;
	}

	if (controller.l_stick_x >= STICK_TRIGGER)
	{
		Serial.printf(STRLN("(controller.l_stick_x >= STICK_TRIGGER)"));
		behavior_curve(TT_ENGINE_DIRECTION_FRONT, TT_ENGINE_DIRECTION_BACK);
		update_engine();
		return;
	}

	reset_engine();
}

void loop()
{
	switch (loop_state)
	{
	case LOOP_STATE_INIT:
		__init__();
		loop_state = LOOP_STATE_UPDATE;
		break;
	case LOOP_STATE_UPDATE:
		__update__();
		break;
	default:
		break;
	}
}
#pragma endregion "Main Loop"

#pragma region "Main Functions"
void update_engine()
{
	Serial.printf("################################################################################################################################\n");
	tt::engine::debug(engine_left, "engine_left");
	tt::engine::debug(engine_right, "engine_right");
	tt::controller::debug(controller, "controller");
	tt::internal::debug("internal");
	tt::engine::move(engine_left, engine_right);
	vTaskDelay(1);
}

void reset_engine()
{
	tt::engine::stop();
	engine_left = TT_ENGINE_FRONT_STOP;
	engine_right = TT_ENGINE_FRONT_STOP;
	tt::internal::setup_millis();
	vTaskDelay(1);
}
#pragma endregion "Main Functions"

#pragma region "Behavior Functions"
void behavior_escape(const uint8_t direction)
{
	const uint8_t base_speed = TT_ENGINE_SPEED_FULL;
	engine_left = {direction, base_speed};
	engine_right = {direction, base_speed};

	if (controller.r_stick_x <= -STICK_TRIGGER)
	{
		engine_left.speed >>= 3;
	}
	else if (controller.r_stick_x >= STICK_TRIGGER)
	{
		engine_right.speed >>= 3;
	}
}

void behavior_forward(const uint8_t direction, const uint8_t speed_modifier)
{
	const uint8_t min_v = speed_modifier >> 2;
	const uint8_t max_v = speed_modifier;
	const uint8_t base_speed = static_cast<uint8_t>(
		TT_INTERNAL_BETWEEN((tt::internal::delta_millis() / 3) * 2 + min_v, min_v, max_v));

	switch (rc_state)
	{
	case RC_STATE_CAREFUL:
		engine_left = {direction, static_cast<uint8_t>(base_speed >> 2)};
		engine_right = {direction, static_cast<uint8_t>(base_speed >> 2)};
		break;

	case RC_STATE_NORMAL:
		engine_left = {direction, base_speed};
		engine_right = {direction, base_speed};
		break;

	default:
		break;
	}

	if (controller.l_stick_x <= -STICK_TRIGGER)
	{
		engine_left.speed = TT_INTERNAL_BETWEEN(engine_left.speed >> 3, TT_ENGINE_SPEED_SLOW(4), TT_ENGINE_SPEED_SLOW(3));
	}
	else if (controller.l_stick_x >= STICK_TRIGGER)
	{
		engine_right.speed = TT_INTERNAL_BETWEEN(engine_left.speed >> 3, TT_ENGINE_SPEED_SLOW(4), TT_ENGINE_SPEED_SLOW(3));
	}
}

void behavior_curve(const uint8_t left_direction, const uint8_t righ_direction)
{
	const uint8_t min_v = TT_ENGINE_SPEED_SLOW(2);
	const uint8_t max_v = TT_ENGINE_SPEED_SLOW(1);
	const uint8_t base_speed = static_cast<uint8_t>(
		TT_INTERNAL_BETWEEN((tt::internal::delta_millis() / 3) * 2 + min_v, min_v, max_v));

	switch (rc_state)
	{
	case RC_STATE_CAREFUL:
		engine_left.speed = static_cast<uint8_t>(base_speed >> 1);
		engine_left.speed = static_cast<uint8_t>(base_speed >> 1);
		break;

	case RC_STATE_NORMAL:
		engine_left.speed = base_speed;
		engine_left.speed = base_speed;
		break;

	default:
		break;
	}
	engine_left.direction = left_direction;
	engine_right.direction = righ_direction;
}

void behavior_accelerated_go()
{
	const uint8_t min_v = TT_ENGINE_SPEED_SLOW(2);
	const uint8_t max_v = TT_ENGINE_SPEED_FULL;
	const uint8_t base_speed = static_cast<uint8_t>(
		TT_INTERNAL_BETWEEN((tt::internal::delta_millis() / 3) * 2 + min_v, min_v, max_v));
	engine_left = {TT_ENGINE_DIRECTION_FRONT, base_speed};
	engine_right = {TT_ENGINE_DIRECTION_FRONT, base_speed};
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
	if (direction == right)
	{
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(70);
		tt::engine::move(TT_ENGINE_FRONT(64), TT_ENGINE_FRONT(255));
		vTaskDelay(196);
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(70);
	}
	else
	{
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(70);
		tt::engine::move(TT_ENGINE_FRONT(255), TT_ENGINE_FRONT(64));
		vTaskDelay(196);
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(70);
	}
}

void macro_curvao(const direction_t direction)
{
	if (direction == right)
	{
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(70);
		tt::engine::move(TT_ENGINE_FRONT(64), TT_ENGINE_FRONT(255));
		vTaskDelay(392);
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(70);
	}
	else
	{
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(70);
		tt::engine::move(TT_ENGINE_FRONT(255), TT_ENGINE_FRONT(64));
		vTaskDelay(392);
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(70);
	}
}

void macro_ladinho(const direction_t direction)
{
	if (direction == right)
	{
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(70);
		tt::engine::move(TT_ENGINE_FRONT(24), TT_ENGINE_FRONT(255));
		vTaskDelay(224);
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(70);
	}
	else
	{
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(70);
		tt::engine::move(TT_ENGINE_FRONT(255), TT_ENGINE_FRONT(24));
		vTaskDelay(224);
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(70);
	}
}
#pragma endregion "Macro Functions"
