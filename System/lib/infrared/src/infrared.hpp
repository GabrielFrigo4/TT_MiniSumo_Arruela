#include <cstddef>
#include <cstdint>

namespace tt
{
namespace infrared
{
enum infrared_t : uint16_t
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
infrared_t receiver();
bool signal(infrared_t sig);
void debug(char *out_buffer, const size_t out_size, const infrared_t infrared, const char *msg);
void debug(const infrared_t infrared, const char *msg);
} // namespace infrared

typedef infrared::infrared_t infrared_t;
} // namespace tt
