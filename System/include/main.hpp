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
#ifndef KERNEL_STATE_AUTO
#define KERNEL_STATE_AUTO 0
#endif
#ifndef KERNEL_STATE_RC
#define KERNEL_STATE_RC 1
#endif
#ifndef KERNEL_STATE_DB
#define KERNEL_STATE_DB 2
#endif
#pragma endregion "Kernel Defines"

#pragma region "Main Signatures"
void boot_init();
void kernel_setup();
void kernel_init();
void kernel_update();
#pragma endregion "Main Signatures"
