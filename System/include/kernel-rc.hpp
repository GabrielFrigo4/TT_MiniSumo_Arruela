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

#pragma region "Trigger Defines"
#ifndef STICK_TRIGGER
#define STICK_TRIGGER 48
#endif
#pragma endregion "Trigger Defines"

#pragma region "State Defines"
#ifndef RC_STATE_CAREFUL
#define RC_STATE_CAREFUL 0
#endif
#ifndef RC_STATE_NORMAL
#define RC_STATE_NORMAL 1
#endif
#pragma endregion "State Defines"

namespace tt::kernel_rc
{
#pragma region "Main Signatures"
	void setup();
	void init();
	void update();
#pragma endregion "Main Signatures"
}
