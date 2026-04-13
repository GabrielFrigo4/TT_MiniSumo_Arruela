#include <cstddef>
#include <cstdint>

#pragma region "Main Data Defines"
#ifndef ROBO_NAME
#define ROBO_NAME "Arruela"
#endif
#ifndef BUFFER_SIZE
#error "[ERRO]: BUFFER_SIZE must be defined before compilation!"
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
#define BOOT_OPTION_AUTO '0'
#endif
#ifndef BOOT_OPTION_RC
#define BOOT_OPTION_RC '1'
#endif
#ifndef BOOT_OPTION_DB
#define BOOT_OPTION_DB '2'
#endif
#ifndef BOOT_OPTION_VALID
#define BOOT_OPTION_VALID(x) (x >= BOOT_OPTION_AUTO && x <= BOOT_OPTION_DB)
#endif
#ifndef BOOT_OPTION_TO_KERNEL_STATE
#define BOOT_OPTION_TO_KERNEL_STATE(x) (x - '0')
#endif
#pragma endregion "Boot Options Defines"

namespace tt::boot
{
#pragma region "Main Signatures"
void setup(char start_mode = '\0');
void init(char start_mode = '\0');
void dispose(char start_mode = '\0');
#pragma endregion "Main Signatures"

#pragma region "Boot Signatures"
uint8_t get_boot();
#pragma endregion "Boot Signatures"
} // namespace tt::boot
