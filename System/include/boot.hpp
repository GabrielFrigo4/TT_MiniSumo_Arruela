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

#pragma region "Boot Options Defines"
#ifndef BOOT_OPTION_AUTO
#define BOOT_OPTION_AUTO '1'
#endif
#ifndef BOOT_OPTION_RC
#define BOOT_OPTION_RC '2'
#endif
#ifndef BOOT_OPTION_DB
#define BOOT_OPTION_DB '3'
#endif
#ifndef BOOT_OPTION_VALID
#define BOOT_OPTION_VALID(x) (x >= '1' && x <= '3')
#endif
#ifndef BOOT_OPTION_TO_STATE
#define BOOT_OPTION_TO_STATE(x) (x - '1')
#endif
#pragma endregion "Boot Options Defines"

namespace tt::boot
{
#pragma region "Main Signatures"
	void setup();
	void init();
	void dispose();
#pragma endregion "Main Signatures"

#pragma region "Boot Signatures"
	uint8_t get_boot();
#pragma endregion "Boot Signatures"
}
