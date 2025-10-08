#include <cstdint>
#include <cstddef>

#pragma region "Main Data Defines"
#ifndef ROBO_NAME
#define ROBO_NAME "Arruela"
#endif
#ifndef BYTE_SIZE
#define BYTE_SIZE 256
#endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE (BYTE_SIZE * 2)
#endif
#ifndef STACK_SIZE
#define STACK_SIZE (BYTE_SIZE * 16)
#endif
#pragma endregion "Main Data Defines"

#pragma region "String Macros"
#ifndef CHARACTER_IS_LOWER_CASE
#define CHARACTER_IS_LOWER_CASE(x) (x >= 'a' && x <= 'z')
#endif
#ifndef CHARACTER_IS_UPPER_CASE
#define CHARACTER_IS_UPPER_CASE(x) (x >= 'A' && x <= 'Z')
#endif
#ifndef CHARACTER_IS_NUMBER
#define CHARACTER_IS_NUMBER(x) (x >= '0' && x <= '9')
#endif
#ifndef STRLN
#define STRLN(x) x "\n"
#endif
#pragma endregion "String Macros"

#pragma region "Command Defines"
#ifndef COMMAND_HELP
#define COMMAND_HELP 'H'
#endif
#ifndef COMMAND_SETUP
#define COMMAND_SETUP '.'
#endif
#ifndef TEST_SENSOR
#define TEST_SENSOR 'S'
#endif
#ifndef TEST_ENGINE
#define TEST_ENGINE 'E'
#endif
#ifndef DEBUG_ENGINE
#define DEBUG_ENGINE 'a'
#endif
#ifndef DEBUG_RECEIVER
#define DEBUG_RECEIVER 'b'
#endif
#ifndef DEBUG_CLOSE
#define DEBUG_CLOSE '-'
#endif
#pragma endregion "Command Defines"

#pragma region "Test Defines"
#ifndef TESTE_REPEAT
#define TESTE_REPEAT 512
#endif
#pragma endregion "Test Defines"

#pragma region "Sensor Defines"
#ifndef SENSOR_USAGE_NONE
#define SENSOR_USAGE_NONE 0
#endif
#ifndef SENSOR_USAGE_ALL
#define SENSOR_USAGE_ALL 1
#endif
#pragma endregion "Sensor Defines"

namespace tt::kernel_db
{
#pragma region "Main Signatures"
	void setup();
	void init();
	void update();
#pragma endregion "Main Signatures"
}
