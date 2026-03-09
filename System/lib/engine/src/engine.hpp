#include <cstdint>
#include <cstddef>

#pragma region "Engine Direction Macros"
#define TT_ENGINE_SENSE_DEFAULT 0
#define TT_ENGINE_SENSE_FRONT 0
#define TT_ENGINE_SENSE_BACK 1
#pragma endregion "Engine Direction Macros"

#pragma region "Engine Speed Macros"
#define TT_ENGINE_SPEED(x) static_cast<uint8_t>(x)
#define TT_ENGINE_SPEED_DEFAULT TT_ENGINE_SPEED(0)
#define TT_ENGINE_SPEED_STOP TT_ENGINE_SPEED(0)
#define TT_ENGINE_SPEED_FULL TT_ENGINE_SPEED(UINT8_MAX)
#define TT_ENGINE_SPEED_SHIFT(x) TT_ENGINE_SPEED(TT_ENGINE_SPEED_FULL >> x)
#pragma endregion "Engine Speed Macros"

#pragma region "Engine Macros"
#define TT_ENGINE_DEFAULT {TT_ENGINE_SENSE_DEFAULT, TT_ENGINE_SPEED_DEFAULT}
#define TT_ENGINE_FRONT_FULL {TT_ENGINE_SENSE_FRONT, TT_ENGINE_SPEED_FULL}
#define TT_ENGINE_BACK_FULL {TT_ENGINE_SENSE_BACK, TT_ENGINE_SPEED_FULL}
#define TT_ENGINE_FRONT_SHIFT(x) {TT_ENGINE_SENSE_FRONT, TT_ENGINE_SPEED_SHIFT(x)}
#define TT_ENGINE_BACK_SHIFT(x) {TT_ENGINE_SENSE_BACK, TT_ENGINE_SPEED_SHIFT(x)}
#define TT_ENGINE_FRONT_STOP {TT_ENGINE_SENSE_FRONT, TT_ENGINE_SPEED_STOP}
#define TT_ENGINE_BACK_STOP {TT_ENGINE_SENSE_BACK, TT_ENGINE_SPEED_STOP}
#define TT_ENGINE_FRONT(x) {TT_ENGINE_SENSE_FRONT, TT_ENGINE_SPEED(x)}
#define TT_ENGINE_BACK(x) {TT_ENGINE_SENSE_BACK, TT_ENGINE_SPEED(x)}
#pragma endregion "Engine Macros"

namespace tt
{
	namespace engine
	{
		struct engine_t
		{
			uint8_t sense;
			uint8_t speed;

			bool operator==(const engine_t &engine) const
			{
				return (sense == engine.sense && speed == engine.speed);
			}
			bool operator!=(const engine_t &engine) const
			{
				return (sense != engine.sense || speed != engine.speed);
			}
		};

		bool get_standby();
		void set_standby(const bool mode);
		void setup();
		void init();
		void move(const engine_t engine_left, const engine_t engine_right);
		void stop();
		void debug(char *out_buffer, const size_t out_size, const engine_t engine, const char *msg);
		void debug(const engine_t engine, const char *msg);
	}

	typedef engine::engine_t engine_t;
}
