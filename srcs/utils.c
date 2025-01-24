#include "fdf.h"
#include "vectors.h"

t_point	add_points(t_point p1, t_point p2)
{
	return ((t_point){p1.x_pos + p2.x_pos, p1.y_pos + p2.y_pos, p1.z_pos + p2.z_pos, p1.color});
}

t_point	offset_point(t_point p, t_v3i offset)
{
	return ((t_point){p.x_pos + offset.x, p.y_pos + offset.y, p.z_pos + offset.z, p.color});
}
