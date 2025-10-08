#include <cstdint>
#include <cstddef>

namespace tt
{
	namespace dualshock4
	{
		struct dualshock4_t
		{
			bool right, down, up, left;
			bool upright, downright, upleft, downleft;
			bool square, cross, circle, triangle;
			bool l1, r1, l2, r2;
			uint8_t l2_value, r2_value;
			int8_t l_stick_x, l_stick_y;
			int8_t r_stick_x, r_stick_y;
		};

		void setup(const char *mac);
		bool is_connected();
		bool disconnected();
		dualshock4_t create_snapshot();
		void debug(char *out_buffer, const size_t out_size, const dualshock4_t dualshock4, const char *msg);
		void debug(const dualshock4_t dualshock4, const char *msg);
	}

	typedef dualshock4::dualshock4_t dualshock4_t;
}