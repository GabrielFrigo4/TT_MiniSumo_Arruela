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
#ifndef COMMAND_CHECK
#define COMMAND_CHECK 'C'
#endif
#ifndef COMMAND_SETUP
#define COMMAND_SETUP '.'
#endif
#ifndef COMMAND_LEFT
#define COMMAND_LEFT '<'
#endif
#ifndef COMMAND_RIGHT
#define COMMAND_RIGHT '>'
#endif
#ifndef ESTRATEGIA_FRENTAO
#define ESTRATEGIA_FRENTAO 'a'
#endif
#ifndef ESTRATEGIA_FRENTINHA
#define ESTRATEGIA_FRENTINHA 'b'
#endif
#ifndef ESTRATEGIA_CURVAO
#define ESTRATEGIA_CURVAO 'c'
#endif
#ifndef ESTRATEGIA_CURVINHA
#define ESTRATEGIA_CURVINHA 'd'
#endif
#ifndef ESTRATEGIA_LADINHO
#define ESTRATEGIA_LADINHO 'e'
#endif
#ifndef ESTRATEGIA_COSTAS
#define ESTRATEGIA_COSTAS 'f'
#endif
#ifndef ESTRATEGIA_DEFESA
#define ESTRATEGIA_DEFESA 'g'
#endif
#ifndef ESTRATEGIA_PRECISO
#define ESTRATEGIA_PRECISO 'h'
#endif
#ifndef ESTRATEGIA_TRANQUILO
#define ESTRATEGIA_TRANQUILO 'i'
#endif
#ifndef ESTRATEGIA_LOOP
#define ESTRATEGIA_LOOP 'z'
#endif
#pragma endregion "Command Defines"

#pragma region "Strategies Defines"
#ifndef ROTATE_SPEED
#define ROTATE_SPEED 96
#endif
#ifndef DEFESA_SPEED
#define DEFESA_SPEED (ROTATE_SPEED - 8)
#endif
#ifndef DEFESA_TRIGGER
#define DEFESA_TRIGGER 0
#endif
#ifndef DEFESA_QUOTA
#define DEFESA_QUOTA 256
#endif
#ifndef PRECISO_TRIGGER
#define PRECISO_TRIGGER 0
#endif
#ifndef PRECISO_QUOTA
#define PRECISO_QUOTA 96
#endif
#ifndef TRANQUILO_TRIGGER
#define TRANQUILO_TRIGGER 0
#endif
#ifndef TRANQUILO_QUOTA
#define TRANQUILO_QUOTA 192
#endif
#pragma endregion "Strategies Defines"

#pragma region "Sensor Defines"
#ifndef SENSOR_USAGE_NONE
#define SENSOR_USAGE_NONE 0
#endif
#ifndef SENSOR_USAGE_ALL
#define SENSOR_USAGE_ALL 1
#endif
#pragma endregion "Sensor Defines"

namespace tt::kernel_auto
{
#pragma region "Main Signatures"
	void setup();
	void init();
	void update();
#pragma endregion "Main Signatures"
}
