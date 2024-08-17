#include <core.hpp>

void Core::begin()
{
	direction = Esquerda;
	running = false;
	running = false;
}

void Core::sensor_task(void *pvParameters)
{
	for (;;)
	{
		if (running)
		{
			if (IrReceiver.decode())
			{
				IrReceiver.resume();
				if (IrReceiver.decodedIRData.command == 0x2)
				{
					digitalWrite(led, 1);
					// stop();
					ESP.restart();
				}
			}

			valueSharpF = digitalRead(sensorF);
			valueSharpD = digitalRead(sensorD);
			valueSharpE = digitalRead(sensorE);

			if (valueSharpE)
			{
				direction = Esquerda;
			}
			else if (valueSharpD)
			{
				direction = Direita;
			}
		}
		vTaskDelay(1);
	}
}

void Core::test_sensors()
{
	SerialBT.println("Test Sensors");
	running = true;
	for (;;)
	{
		SerialBT.printf("ESQ: %d, FEN: %d, DIR: %d\n", valueSharpE, valueSharpF, valueSharpD);
		delay(15);
	}
}

void Core::test_wotors_wth_sensors()
{
	digitalWrite(stby, 1);
	SerialBT.println("Test Motors With Sensors");
	running = true;
	for (;;)
	{
		SerialBT.printf("ESQ: %d, FEN: %d, DIR: %d\n", valueSharpE, valueSharpF, valueSharpD);

		if (valueSharpF)
			forward(255, 255);
		else if (valueSharpE)
			left(80, 80);
		else if (valueSharpD)
			right(80, 80);
		else
			stop();
	}
}

void Core::stop()
{
	digitalWrite(a2, 1);
	digitalWrite(b1, 1);
	digitalWrite(b2, 1);
}

void Core::move(uint32_t pa, uint32_t pb)
{
}

void Core::backward(uint32_t pa, uint32_t pb)
{
	digitalWrite(b1, 0);
	digitalWrite(b2, 1);
	digitalWrite(a1, 1);
	digitalWrite(a2, 0);
	analogWrite(pwmB, pb);
	analogWrite(pwmA, pa);
}
void Core::forward(uint32_t pa, uint32_t pb)
{

	digitalWrite(b1, 1);
	digitalWrite(b2, 0);
	digitalWrite(a1, 0);
	digitalWrite(a2, 1);
	analogWrite(pwmB, pb);
	analogWrite(pwmA, pa);
}
void Core::right(uint32_t pa, uint32_t pb)
{
	digitalWrite(b1, 1);
	digitalWrite(b2, 0);
	digitalWrite(a1, 1);
	digitalWrite(a2, 0);
	analogWrite(pwmB, pb);
	analogWrite(pwmA, pa);
}
void Core::left(uint32_t pa, uint32_t pb)
{
	digitalWrite(b1, 0);
	digitalWrite(b2, 1);
	digitalWrite(a1, 0);
	digitalWrite(a2, 1);
	analogWrite(pwmB, pb);
	analogWrite(pwmA, pa);
}

void Core::procurar_defesa()
{
}

void Core::procurar_padrao(uint32_t velocidade_giro)
{
}