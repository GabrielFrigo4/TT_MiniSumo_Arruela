#include <cstdint>
#include <cstddef>

#pragma region "Main Data Defines"
#define ROBO_NAME "Arruela"
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

#pragma region "Main Loop Defines"
#define LOOP_STATE_INIT 0
#define LOOP_STATE_UPDATE 1
#define STICK_TRIGGER 48
#pragma endregion "Main Loop Defines"

#pragma region "Main State Defines"
#define RC_STATE_CAREFUL 0
#define RC_STATE_NORMAL 1
#pragma endregion "Main State Defines"

#pragma region "Main Macros"
#define STRLN(x) x "\n"
#pragma endregion "Main Macros"

#pragma region "Main Types"
enum direction_t
{
	left,
	right,
};
#pragma endregion "Main Types"

#pragma region "Main Signatures"
void __init__();
void __update__();
void update_engine();
void reset_engine();
void behavior_just_go();
void behavior_accelerated_go();
void behavior_escape(const uint8_t direction);
void behavior_forward(const uint8_t direction, const uint8_t speed_modifier);
void behavior_curve(const uint8_t left_direction, const uint8_t righ_direction);
void macro_curvinha(const direction_t left_direction);
void macro_curvao(const direction_t left_direction);
void macro_ladinho(const direction_t left_direction);
#pragma endregion "Main Signatures"