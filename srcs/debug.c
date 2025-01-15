#include "fdf.h"

void	copy_point(t_point source, t_point *dest)
{
	dest->x_pos = source.x_pos;
	dest->y_pos = source.y_pos;
	dest->z_pos = source.z_pos;
	dest->color = source.color;
}
