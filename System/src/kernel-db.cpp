#include <Arduino.h>
#include <engine.hpp>
#include <infrared.hpp>
#include <internal.hpp>
#include <sensor.hpp>
#include <serial.hpp>
#include <utilitie.hpp>
#include "kernel-db.hpp"

namespace tt::kernel_db
{
#pragma region "Signatures"
	void debug_engine(const tt::engine_t engine_left, const tt::engine_t engine_right, const int timer);
	void debug_receiver();
	void test_sensor();
	void test_engine();
	void sensor_task(void *pvParameters);
	void setup_task();
	void setup_connect();
	void setup_debug();
	void setup();
	void init();
	void update();
#pragma endregion "Signatures"

#pragma region "Templates Signatures"
	template <typename T>
	void setup_data(const char *msg, T &data);
#pragma endregion "Templates Signatures"

#pragma region "State Data"
	bool running = true;
#pragma endregion "State Data"

#pragma region "Input Data"
	char bluetooth_input_char = DEBUG_ENGINE;
	char debug = bluetooth_input_char;
#pragma endregion "Input Data"

#pragma region "Debug Data"
	tt::engine_t engine_left = TT_ENGINE_FRONT(32);
	tt::engine_t engine_right = TT_ENGINE_FRONT(32);
	int timer = 1 << 10;
#pragma endregion "Debug Data"

#pragma region "Sensor Data"
	tt::sensor_t sensor;
#pragma endregion "Sensor Data"

#pragma region "Main Functions"
	void setup()
	{
		tt::internal::setup();
		tt::internal::set_led(false);
		Serial.printf(STRLN("Setup Internal!"));
		Serial.printf(STRLN("Mac Address: %s"), tt::internal::mac_address());
		vTaskDelay(512);

		tt::engine::setup();
		Serial.printf(STRLN("Setup Engine!"));

		tt::sensor::setup();
		Serial.printf(STRLN("Setup Sensor!"));

		tt::infrared::setup();
		Serial.printf(STRLN("Setup Infrared!"));

		setup_task();
		Serial.printf(STRLN("Setup Task!"));

		setup_connect();
		Serial.printf(STRLN("Setup Connect!"));
	}

	void init()
	{
		tt::engine::init();
	}

	void update()
	{
		setup_debug();
		tt::serial::printf(STRLN("Setup Debug!"));

		int TEST = 213;
		switch (debug)
		{
		case DEBUG_ENGINE:
			tt::serial::printf(STRLN("Begin Debug Engine!"));
			setup_data("Motor Esquerdo Direção", engine_left.direction);
			setup_data("Motor Esquerdo Velocidade", engine_left.speed);
			setup_data("Motor Direito Direção", engine_right.direction);
			setup_data("Motor Direito Velocidade", engine_right.speed);
			setup_data("Tempo de Duração em Milissegundos", timer);
			debug_engine(engine_left, engine_right, timer);
			tt::serial::printf(STRLN("End Debug Engine!"));
			break;
		case DEBUG_RECEIVER:
			tt::serial::printf(STRLN("Begin Debug Receiver!"));
			debug_receiver();
			tt::serial::printf(STRLN("End Debug Receiver!"));
			break;
		case DEBUG_CLOSE:
			return;
			break;
		default:
			return;
			break;
		}
	}
#pragma endregion "Main Functions"

#pragma region "Setup Functions"
	template <typename T>
	void setup_data(const char *msg, T &data)
	{
		tt::serial::flush();
		tt::serial::print(msg);
		tt::serial::printf(STRLN(" (%i):"), data);
		tt::serial::wait();
		String in = tt::serial::input();
		if (in.length() > 1)
		{
			data = in.toInt();
		}
		tt::serial::printf(STRLN("[data-set] => (%i)"), data);
	}

	void setup_task()
	{
		running = true;
		TaskHandle_t SensorTask;
		xTaskCreatePinnedToCore(sensor_task, "SensorTask", 256 * 16, nullptr, 16, &SensorTask, PRO_CPU_NUM);
		vTaskDelay(512);
	}

	void setup_connect()
	{
		while (!tt::serial::enabled())
		{
			vTaskDelay(1);
		}

		tt::serial::printf(STRLN("LIGOUUUU"));
		tt::serial::printf(STRLN("Digite '%c' para Mostrar os Comandos Disponíveis!"), COMMAND_HELP);
	}

	void setup_debug()
	{
		bluetooth_input_char = DEBUG_ENGINE;
		debug = bluetooth_input_char;

		while (bluetooth_input_char != COMMAND_SETUP)
		{
			vTaskDelay(1);
			if (tt::serial::available())
			{
				bluetooth_input_char = tt::serial::read();
			}
			else
			{
				continue;
			}

			switch (bluetooth_input_char)
			{
			case COMMAND_HELP:
				tt::serial::clear();
				tt::serial::printf(STRLN("+-----------------+"));
				tt::serial::printf(STRLN("| UM HELP PRA TU! |"));
				tt::serial::printf(STRLN("+-----------------+"));
				tt::serial::printf(STRLN("+-------------------------------+"));
				tt::serial::printf(STRLN("| Todos os Comandos (MAIÚSCULA) |"));
				tt::serial::printf(STRLN("+-------------------------------+"));
				tt::serial::printf(STRLN("\"Comando\" -> \"Nome\""));
				tt::serial::printf(STRLN("\"%c\" -> \"%s\""), COMMAND_HELP, "HELP");
				tt::serial::printf(STRLN("+-----------------------------+"));
				tt::serial::printf(STRLN("| Todos os Testes (MAIÚSCULA) |"));
				tt::serial::printf(STRLN("+-----------------------------+"));
				tt::serial::printf(STRLN("\"Teste\" -> \"Nome\""));
				tt::serial::printf(STRLN("\"%c\" -> \"%s\""), TEST_SENSOR, "SENSOR");
				tt::serial::printf(STRLN("\"%c\" -> \"%s\""), TEST_ENGINE, "ENGINE");
				tt::serial::printf(STRLN("+-----------------------------+"));
				tt::serial::printf(STRLN("| Todas os Debugs (MINÚSCULA) |"));
				tt::serial::printf(STRLN("+-----------------------------+"));
				tt::serial::printf(STRLN("\"Debug\" -> \"Nome\""));
				tt::serial::printf(STRLN("\"%c\" -> \"%s\""), DEBUG_ENGINE, "ENGINE");
				tt::serial::printf(STRLN("\"%c\" -> \"%s\""), DEBUG_RECEIVER, "RECEIVER");
				tt::serial::printf(STRLN("\"%c\" -> \"%s\""), DEBUG_CLOSE, "CLOSE");
				break;

			case TEST_SENSOR:
				test_sensor();
				break;

			case TEST_ENGINE:
				test_engine();
				break;

			case DEBUG_CLOSE:
				running = false;
				tt::serial::printf(STRLN("+-------------+"));
				tt::serial::printf(STRLN("| CLOSE DEBUG |"));
				tt::serial::printf(STRLN("+-------------+"));
				continue;
				break;

			case COMMAND_SETUP:
				tt::serial::printf(STRLN("+------------------+"));
				tt::serial::printf(STRLN("| SETUP FINALIZADO |"));
				tt::serial::printf(STRLN("+------------------+"));
				continue;
				break;

			default:
				if (CHARACTER_IS_LOWER_CASE(bluetooth_input_char))
				{
					debug = bluetooth_input_char;
					switch (bluetooth_input_char)
					{
					case DEBUG_ENGINE:
						tt::serial::printf(STRLN("+-------+-----------+"));
						tt::serial::printf(STRLN("| Debug | ENGINE!!! |"));
						tt::serial::printf(STRLN("+-------+-----------+"));
						break;

					case DEBUG_RECEIVER:
						tt::serial::printf(STRLN("+-------+-------------+"));
						tt::serial::printf(STRLN("| Debug | RECEIVER!!! |"));
						tt::serial::printf(STRLN("+-------+-------------+"));
						break;

					default:
						break;
					}
				}
				break;
			}
		}

		tt::serial::erase();
	}
#pragma endregion "Setup Functions"

#pragma region "Tesk Functions"
	void sensor_task(void *pvParameters)
	{
		while (running)
		{
			vTaskDelay(1);
			sensor = tt::sensor::create_snapshot();
		}

		tt::internal::set_led(true);
		tt::engine::stop();
		tt::engine::set_standby(true);
		tt::serial::end();
		ESP.restart();
	}
#pragma endregion "Tesk Functions"

#pragma region "Debug Functions"
	void debug_engine(const tt::engine_t engine_left, const tt::engine_t engine_right, const int timer)
	{
		tt::engine::stop();
		tt::engine::move(engine_left, engine_right);
		vTaskDelay(timer);
		tt::engine::stop();
	}

	void debug_receiver()
	{
		bool ready = false;
		bool update = false;
		do
		{
			vTaskDelay(1);
			update = tt::infrared::update();
			if (!update)
			{
				continue;
			}
			switch (tt::infrared::receiver())
			{
			case tt::infrared_t::test:
				ready = true;
				for (int i = 0; i < 3; i++)
				{
					tt::internal::set_led(true);
					vTaskDelay(48);
					tt::internal::set_led(false);
					vTaskDelay(48);
				}
				break;
			case tt::infrared_t::begin:
				if (ready)
				{
					break;
				}
				for (int i = 0; i < 2; i++)
				{
					tt::internal::set_led(true);
					vTaskDelay(96);
					tt::internal::set_led(false);
					vTaskDelay(96);
				}
				break;
			case tt::infrared_t::end:
				for (int i = 0; i < 2; i++)
				{
					tt::internal::set_led(true);
					vTaskDelay(144);
					tt::internal::set_led(false);
					vTaskDelay(144);
				}
				break;
			}
		} while (!(ready && tt::infrared::receiver() == tt::infrared_t::begin));

		for (int i = 0; i < 3; i++)
		{
			tt::internal::set_led(true);
			vTaskDelay(144);
			tt::internal::set_led(false);
			vTaskDelay(144);
		}

		while (!tt::infrared::signal(tt::infrared_t::end))
		{
			vTaskDelay(1);
		}

		for (int i = 0; i < 2; i++)
		{
			tt::internal::set_led(true);
			vTaskDelay(432);
			tt::internal::set_led(false);
			vTaskDelay(432);
		}
	}
#pragma endregion "Debug Functions"

#pragma region "Test Functions"
	void test_sensor()
	{
		for (int count = 0; count < TESTE_REPEAT; count++)
		{
			char buff[BUFFER_SIZE];
			tt::sensor::debug(buff, BUFFER_SIZE, sensor, "sensor");
			tt::serial::printf(buff);
			vTaskDelay(32);
		}
		tt::serial::clear();
		tt::serial::printf(STRLN("END TEST SENSOR!"));
	}

	void test_engine()
	{
		tt::serial::printf(STRLN("(LEFT: FRONT) (RIGHT: FRONT)"));
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(3072);
		tt::engine::stop();
		vTaskDelay(512);
		tt::serial::printf(STRLN("(LEFT: FRONT) (RIGHT: BACK)"));
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(3072);
		tt::engine::stop();
		vTaskDelay(512);
		tt::serial::printf(STRLN("(LEFT: BACK) (RIGHT: FRONT)"));
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_FRONT_FULL);
		vTaskDelay(3072);
		tt::engine::stop();
		vTaskDelay(512);
		tt::serial::printf(STRLN("(LEFT: BACK) (RIGHT: BACK)"));
		tt::engine::move(TT_ENGINE_BACK_FULL, TT_ENGINE_BACK_FULL);
		vTaskDelay(3072);
		tt::engine::stop();
		vTaskDelay(512);
		tt::serial::printf(STRLN("(LEFT: FAST FRONT) (RIGHT: SLOW FRONT)"));
		tt::engine::move(TT_ENGINE_FRONT_FULL, TT_ENGINE_FRONT_SLOW(4));
		vTaskDelay(3072);
		tt::engine::stop();
		vTaskDelay(512);
		tt::serial::printf(STRLN("(LEFT: SLOW FRONT) (RIGHT:  FAST FRONT)"));
		tt::engine::move(TT_ENGINE_FRONT_SLOW(4), TT_ENGINE_FRONT_FULL);
		vTaskDelay(3072);
		tt::engine::stop();
		tt::serial::printf(STRLN("END TEST ENGINE!"));
	}
#pragma endregion "Test Functions"
}
