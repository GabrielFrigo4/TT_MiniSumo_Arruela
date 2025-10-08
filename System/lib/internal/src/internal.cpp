#include <Arduino.h>
#include <WiFi.h>
#include <esp_bt.h>
#include <esp_bt_main.h>
#include <esp_bt_device.h>
#include <esp_gap_bt_api.h>
#include <nvs_flash.h>
#include "internal.hpp"

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

#pragma region "Internal Pinning Macros"
#ifndef LED
#define LED 2
#endif
#pragma endregion "Internal Pinning Macros"

namespace tt::internal
{
	char wifi_mac_address[32] = {};
	uint64_t internal_millis = 0;
	uint64_t internal_micros = 0;
	bool led_mode = false;

	void setup()
	{
		pinMode(LED, OUTPUT);
		setup_millis();
		setup_micros();
		WiFi.macAddress().toCharArray(wifi_mac_address, sizeof(wifi_mac_address));
	}

	bool get_led()
	{
		return led_mode;
	}

	void set_led(const bool mode)
	{
		if (led_mode != mode)
		{
			led_mode = mode;
			digitalWrite(LED, static_cast<uint8_t>(led_mode));
		}
	}

	void setup_millis()
	{
		internal_millis = end_millis();
	}

	uint64_t begin_millis()
	{
		return internal_millis;
	}

	uint64_t end_millis()
	{
		return millis();
	}

	uint64_t delta_millis()
	{
		return end_millis() - begin_millis();
	}

	void setup_micros()
	{
		internal_micros = end_micros();
	}

	uint64_t begin_micros()
	{
		return internal_micros;
	}

	uint64_t end_micros()
	{
		return micros();
	}

	uint64_t delta_micros()
	{
		return end_micros() - begin_micros();
	}

	const char *mac_address()
	{
		return wifi_mac_address;
	}

	void bluetooth_disable()
	{
		esp_bluedroid_disable();
		esp_bluedroid_deinit();
		esp_bt_controller_disable();
		vTaskDelay(128);
		esp_bt_controller_deinit();
		vTaskDelay(128);
		esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
		esp_bt_controller_mem_release(ESP_BT_MODE_BLE);
		esp_bt_controller_mem_release(ESP_BT_MODE_BTDM);
		vTaskDelay(1024);
	}

	void bluetooth_enable()
	{
		esp_bt_controller_config_t bt_config = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
		esp_bt_controller_init(&bt_config);
		esp_bt_controller_enable(ESP_BT_MODE_BTDM);
		esp_bluedroid_init();
		esp_bluedroid_enable();
		vTaskDelay(1024);
	}

	void bluetooth_restart()
	{
		bluetooth_disable();
		bluetooth_enable();
	}

	void flash_restart()
	{
		nvs_flash_erase();
		nvs_flash_init();
	}

	void debug(char *out_buffer, const size_t out_size, const char *msg)
	{
		snprintf(out_buffer, out_size - 1, "\"%s\" = { begin:%lli; end:%lli; delta:%lli }\n", msg,
				 begin_millis(), end_millis(), delta_millis());
	}

	void debug(const char *msg)
	{
		char buffer[BUFFER_SIZE];
		debug(buffer, BUFFER_SIZE, msg);
		Serial.print(buffer);
	}
}