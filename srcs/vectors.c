#include "vectors.h"

t_v3i		add_v3i(t_v3i v1, t_v3i v2)
{
	return ((t_v3i){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}
