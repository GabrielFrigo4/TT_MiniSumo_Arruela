#define DECODE_SONY

#include <BluetoothSerial.h>
#include <Arduino.h>
#include <IRremote.hpp>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char BT = 'f';         // char que é recebida pelo bluetooth
char estrategia = 'f'; // estratégio de início da luta (qualquer caracter)

#define sensorF 39
#define sensorE 34
// #define sensorFd 39
// #define sensorFe 35
#define sensorD 36

#define pwmB 4
#define b1 17
#define b2 16
#define stby 5
#define a1 18
#define a2 19
#define pwmA 23

#define led 2
#define IR 13

enum Direction
{
    esq,
    dir
};
Direction direc = esq;

#pragma region motorController
void stop()
{
    digitalWrite(a1, 1);
    digitalWrite(a2, 1);
    digitalWrite(b1, 1);
    digitalWrite(b2, 1);
}
void backward(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
void forward(uint32_t pa, uint32_t pb)
{

    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
void right(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 1);
    digitalWrite(b2, 0);
    digitalWrite(a1, 1);
    digitalWrite(a2, 0);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
void left(uint32_t pa, uint32_t pb)
{
    digitalWrite(b1, 0);
    digitalWrite(b2, 1);
    digitalWrite(a1, 0);
    digitalWrite(a2, 1);
    analogWrite(pwmB, pb);
    analogWrite(pwmA, pa);
}
#pragma endregion motorController

TaskHandle_t SensorTask;

bool valueSharpE, valueSharpD;
bool running = false;
int valueSharpF;
void FunctionSensorTask(void *pvParameters)
{
    // SerialBT.print("FunctionSensorTask running on core ");
    // SerialBT.println(xPortGetCoreID());
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
                    stop();
                    ESP.restart();
                }
            }
            // vTaskDelay(15);
            valueSharpF = digitalRead(sensorF);
            valueSharpD = digitalRead(sensorD);
            valueSharpE = digitalRead(sensorE);

            if (valueSharpE)
            {
                direc = esq;
            }
            else if (valueSharpD)
            {
                direc = dir;
            }
        }
        vTaskDelay(1);
    }
}

#pragma region testsRegion
void testSensors()
{
    SerialBT.println("Test Sensors");
    running = true;
    for (;;)
    {
        SerialBT.printf("ESQ: %d, FEN: %d, DIR: %d\n", valueSharpE, valueSharpF, valueSharpD);
        delay(15);
    }
}

void testMotorsWithSensors()
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
#pragma endregion testsRegion

void setup()
{
    pinMode(pwmB, OUTPUT);
    pinMode(b1, OUTPUT);
    pinMode(b2, OUTPUT);
    pinMode(stby, OUTPUT);
    pinMode(a1, OUTPUT);
    pinMode(a2, OUTPUT);
    pinMode(pwmA, OUTPUT);
    pinMode(sensorD, INPUT);
    pinMode(sensorE, INPUT);
    pinMode(sensorF, INPUT);
    // pinMode(sensorFd, INPUT);
    // pinMode(sensorFe, INPUT);
    pinMode(led, OUTPUT);
    digitalWrite(stby, 0);

    IrReceiver.begin(IR, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
    printActiveIRProtocols(&Serial);

    SerialBT.begin("Arruela"); // Bluetooth device name
    SerialBT.println("LIGOUUUU");

    xTaskCreatePinnedToCore(FunctionSensorTask, "SensorTask", 10000, NULL, 1, &SensorTask, 0);
    delay(500);

    while (BT != '0')
    { // Inicio quando bluetooth recebe o char '0'
        if (SerialBT.available())
        {
            BT = SerialBT.read();
            SerialBT.println(BT);
        }
        if (BT == '<')
        { // definir para que lado será toda a progrmação
            direc = esq;
        }
        else if (BT == '>')
        {
            direc = dir;
        }
        else if (BT == 'C')
        { // Char 'C' checa as estrategias
            SerialBT.println("Check");
            SerialBT.print("Estrategia: ");
            SerialBT.println(estrategia);
            SerialBT.print("Direc: ");
            if (direc == dir)
                SerialBT.println("direita");
            else
                SerialBT.println("esquerda");
        }
        else if (BT == 'S')
        { // Char 'S'teste sensor
            testSensors();
        }
        else if (BT == 'M')
        { // Char 'M'teste motor com sensor
            testMotorsWithSensors();
        }
        else if (BT == '0')
        {
            break;
        }
        else
        {
            if (!(BT == 13 || BT == 10 || (BT > 48 && BT < 58)))
            { // Se não for ENTER ou numero altera a estrategia inicial
                estrategia = BT;
            }
        }
    }

    bool ready = false;
    while (true)
    {
        if (IrReceiver.decode())
        {
            IrReceiver.resume();
            if (IrReceiver.decodedIRData.command == 0x0)
            {
                ready = true;
                for (int i = 0; i < 3; i++)
                {
                    digitalWrite(led, 1);
                    delay(50);
                    digitalWrite(led, 0);
                    delay(50);
                    if (IrReceiver.decode())
                    {
                        IrReceiver.resume();
                        if (IrReceiver.decodedIRData.command == 0x1 && ready)
                        {
                            digitalWrite(led, 0);
                            digitalWrite(stby, 1);
                            break;
                        }
                    }
                }
            }

            if (IrReceiver.decodedIRData.command == 0x1 && ready)
            {
                digitalWrite(led, 0);
                digitalWrite(stby, 1);
                break;
            }
        }
    }

    SerialBT.println("COMECOUUUUU");
    running = true;

    switch (estrategia)
    {
    case 'a': // frentao
        forward(255, 255);
        SerialBT.print("FRENTAAO");
        delay(200);
        break;

    case 'b': // curvao
        if (direc == dir)
        {
            // right(255, 255);
            // delay(25);
            forward(255, 170);
            delay(600);
            left(255, 255);
            delay(100);
            direc = esq;
        }
        else
        {
            left(255, 255);
            delay(25);
            forward(255, 170);
            delay(600);
            right(255, 255);
            delay(100);
            direc = dir;
        }
        break;

    case 'c': // curvinha
        if (direc == dir)
        {
            right(255, 255);
            delay(90);
            forward(100, 255);
            delay(300);
            left(255, 255);
            delay(200);
            direc = esq;
        }
        else
        {
            left(255, 255);
            delay(90);
            forward(255, 100);
            delay(300);
            right(255, 255);
            delay(200);
            direc = dir;
        }
        break;
        //
        // case 'd': // babacas
        //    if (direc == dir)
        //    {
        //        move('D', 'T', 100);
        //        move('E', 'F', 100);
        //        delay(50);
        //        move('D', 'F', 100);
        //        move('E', 'F', 100);
        //        delay(250);
        //        move('D', 'F', 100);
        //        move('E', 'T', 100);
        //        delay(120);
        //        direc = esq;
        //    }
        //    else
        //    {
        //        move('D', 'F', 100);
        //        move('E', 'T', 100);
        //        delay(50);
        //        move('D', 'F', 100);
        //        move('E', 'F', 100);
        //        delay(250);
        //        move('D', 'T', 100);
        //        move('E', 'F', 100);
        //        delay(120);
        //        direc = dir;
        //    }
        //    break;
        //
    case 'e': // costas   - só gira 180º
        if (direc == dir)
        { // prestar atenção na direc, pq os robôs estarão de costas
            right(255, 255);
            delay(190);
        }
        else
        {
            left(255, 255);
            delay(190);
        }
        break;

    case 'l': // frentao
        forward(255, 255);
        SerialBT.print("FRENTAAO");
        delay(600);
        break;

    case 'f': // vai direto pro loop
        break;

        // case 'g': // costas curvao
        //     if (direc == dir)
        //     {
        //         // move('D', 'F', 50);
        //         // move('E', 'F', 100);
        //         delay(200);
        //     }
        //     else
        //     {
        //         // move('D', 'F', 100);
        //         // move('E', 'F', 50);
        //         delay(200);
        //     }
        //     break;

    default: // CÓPIA DO FRENTÃO
        forward(255, 255);
        delay(500);
        SerialBT.print("DEFAAAAAAULT");
        break;
    }

    // stop();
    // ESP.restart();
}

void loop()
{

    if (valueSharpF)
    {
        while (valueSharpF)
        {
            forward(255, 255);
        }
    }
    else if (valueSharpE)
    {
        left(170, 170);
        direc = esq;
    }
    else if (valueSharpD)
    {
        right(170, 170);
        direc = dir;
    }
    else
    {
        if (direc == esq)
            left(170, 170);
        else
            right(170, 170);
    }
}
