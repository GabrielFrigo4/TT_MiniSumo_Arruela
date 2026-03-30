#include <cstddef>
#include <cstdint>

namespace tt
{
namespace sensor
{
enum sensor_mode_t : uint16_t
{
	sender = 0,
	receiver = 1,
	none = 2
};

struct sensor_t
{
	int left;
	int front;
	int right;
	sensor_mode_t mode;
};

void setup();
void init();
sensor_t create_snapshot();
sensor_mode_t get_mode();
void set_mode(sensor_mode_t mode);
void debug(char *out_buffer, const size_t out_size, const sensor_t sensor, const char *msg);
void debug(const sensor_t sensor, const char *msg);
} // namespace sensor

typedef sensor::sensor_t sensor_t;
typedef sensor::sensor_mode_t sensor_mode_t;
} // namespace tt
