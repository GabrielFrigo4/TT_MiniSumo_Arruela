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

#pragma region "Loop Defines"
#ifndef LOOP_STATE_BOOT_INIT
#define LOOP_STATE_BOOT_INIT 0
#endif
#ifndef LOOP_STATE_KERNEL_SETUP
#define LOOP_STATE_KERNEL_SETUP 1
#endif
#ifndef LOOP_STATE_KERNEL_INIT
#define LOOP_STATE_KERNEL_INIT 2
#endif
#ifndef LOOP_STATE_KERNEL_UPDATE
#define LOOP_STATE_KERNEL_UPDATE 3
#endif
#pragma endregion "Loop Defines"

#pragma region "Kernel Defines"
#ifndef DEFAULT_KERNEL_STATE
#error "[ERRO]: DEFAULT_KERNEL_STATE must be defined before compilation!"
#endif
#ifndef KERNEL_STATE_AUTO
#define KERNEL_STATE_AUTO 0
#endif
#ifndef KERNEL_STATE_RC
#define KERNEL_STATE_RC 1
#endif
#ifndef KERNEL_STATE_DB
#define KERNEL_STATE_DB 2
#endif
#ifndef KERNEL_STATE_TO_BOOT_OPTION
#define KERNEL_STATE_TO_BOOT_OPTION(x) (x + '0')
#endif
#pragma endregion "Kernel Defines"

#pragma region "Main Signatures"
void boot_init();
void kernel_setup();
void kernel_init();
void kernel_update();
#pragma endregion "Main Signatures"
