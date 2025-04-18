#include <cstdint>
#include <cstddef>

namespace tt
{
	namespace receiver
	{
		enum receiver_t : uint16_t
		{
			test = 0,
			begin = 1,
			end = 2,
			none = 3
		};
		void setup();
		bool decode();
		void resume();
		uint16_t command();
		bool update();
		receiver_t receiver();
		bool signal(receiver_t sig);
		void debug(char *out_buffer, const size_t out_size, receiver_t receiver, const char *msg);
		void debug(receiver_t receiver, const char *msg);
	}

	typedef receiver::receiver_t receiver_t;
}