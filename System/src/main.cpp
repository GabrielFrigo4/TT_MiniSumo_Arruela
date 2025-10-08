#include <Arduino.h>
#include "boot.hpp"
#include "kernel-auto.hpp"
#include "kernel-rc.hpp"
#include "kernel-db.hpp"
#include "main.hpp"

#pragma region "State Data"
uint8_t loop_state = LOOP_STATE_BOOT_INIT;
uint8_t kernel_state = KERNEL_STATE_DB;
#pragma endregion "State Data"

#pragma region "Setup Functions"
void setup()
{
	tt::boot::setup();
}
#pragma endregion "Setup Functions"

#pragma region "Loop Functions"
void boot_init()
{
	tt::boot::init();
	kernel_state = tt::boot::get_boot();
	tt::boot::dispose();
}

void kernel_setup()
{
	switch (kernel_state)
	{
	case KERNEL_STATE_AUTO:
		tt::kernel_auto::setup();
		break;
	case KERNEL_STATE_RC:
		tt::kernel_rc::setup();
		break;
	case KERNEL_STATE_DB:
		tt::kernel_db::setup();
		break;
	default:
		break;
	}
}

void kernel_init()
{
	switch (kernel_state)
	{
	case KERNEL_STATE_AUTO:
		tt::kernel_auto::init();
		break;
	case KERNEL_STATE_RC:
		tt::kernel_rc::init();
		break;
	case KERNEL_STATE_DB:
		tt::kernel_db::init();
		break;
	default:
		break;
	}
}

void kernel_update()
{
	switch (kernel_state)
	{
	case KERNEL_STATE_AUTO:
		tt::kernel_auto::update();
		break;
	case KERNEL_STATE_RC:
		tt::kernel_rc::update();
		break;
	case KERNEL_STATE_DB:
		tt::kernel_db::update();
		break;
	default:
		break;
	}
}

void loop()
{
	switch (loop_state)
	{
	case LOOP_STATE_BOOT_INIT:
		boot_init();
		loop_state = LOOP_STATE_KERNEL_SETUP;
		break;
	case LOOP_STATE_KERNEL_SETUP:
		kernel_setup();
		loop_state = LOOP_STATE_KERNEL_INIT;
		break;
	case LOOP_STATE_KERNEL_INIT:
		kernel_init();
		loop_state = LOOP_STATE_KERNEL_UPDATE;
		break;
	case LOOP_STATE_KERNEL_UPDATE:
		kernel_update();
		break;
	default:
		break;
	}
}
#pragma endregion "Loop Functions"
