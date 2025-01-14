/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:04:02 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/14 23:11:01 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "vectors.h"

t_v3	calculate_isometric(t_v3 *vec, t_map_info *map)
{
	t_v3	result;

	(void)map;
	result.x = vec->x;
	result.y = vec->y;
	result.z = vec->z;
	return (result);
}

void	draw_line(t_point *p0, t_point *p1, t_map_info *map)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;

	dx = abs((int)p1->x_pos - (int)p0->x_pos);
	sx = ((int)p0->x_pos < (int)p1->x_pos) * 2 - 1;
	dy = -abs((int)p1->y_pos - (int)p0->y_pos);
	sy = ((int)p0->y_pos < (int)p1->y_pos) * 2 - 1;
	error = dx + dy;
	while (true)
	{
		my_mlx_pixel_put(map, (int)p0->x_pos, (int)p0->y_pos, 0xffffff);
		if ((int)p0->x_pos == (int)p1->x_pos
			&& (int)p0->y_pos == (int)p1->y_pos)
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			error = error + dy;
			p0->x_pos = (int)p0->x_pos + sx;
		}
		if (e2 <= dx)
		{
			error = error + dx;
			p0->y_pos = (int)p0->y_pos + sy;
		}
	}
}

void	calculate_point(t_point *p, t_map_info *map, t_point og)
{
	float	rad_x;
	float	rad_y;
	float	rad_z;

	float temp_x, temp_y, temp_z;
	rad_x = (int)map->rotation.x * M_PI / 180.0;
	rad_y = (int)map->rotation.y * M_PI / 180.0;
	rad_z = (int)map->rotation.z * M_PI / 180.0;
	temp_y = og.y_pos * cos(rad_x) - og.z_pos * sin(rad_x);
	temp_z = og.y_pos * sin(rad_x) + og.z_pos * cos(rad_x);
	og.y_pos = temp_y;
	og.z_pos = temp_z;
	temp_x = og.x_pos * cos(rad_y) + og.z_pos * sin(rad_y);
	temp_z = -og.x_pos * sin(rad_y) + og.z_pos * cos(rad_y);
	og.x_pos = temp_x;
	og.z_pos = temp_z;
	temp_x = og.x_pos * cos(rad_z) - og.y_pos * sin(rad_z);
	temp_y = og.x_pos * sin(rad_z) + og.y_pos * cos(rad_z);
	og.x_pos = temp_x;
	og.y_pos = temp_y;
	p->x_pos = og.x_pos;
	p->y_pos = og.y_pos;
	p->z_pos = og.z_pos;
}

void	render_image(t_map_info *map)
{
	short	y;
	short	x;
	t_point	curr;

	printf("Rendering...\n");
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			(void)curr;
			copy_point(map->map[y][x], &curr);
			calculate_point(&curr, map, map->map[y][x]);
			if (curr.z_pos == 0)
				my_mlx_pixel_put(map, curr.x_pos, curr.y_pos, 0xffffff);
			else if (curr.z_pos == 10)
				my_mlx_pixel_put(map, curr.x_pos, curr.y_pos, 0xff0000);
			copy_point(curr, &map->map[y][x]);
			if (x != 0)
				draw_line(&map->map[y][x], &map->map[y][x - 1], map);
			copy_point(curr, &map->map[y][x]);
			if (y != 0)
				draw_line(&map->map[y][x], &map->map[y - 1][x], map);
			copy_point(curr, &map->map[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->screen.mlx, map->screen.win,
		map->screen.img.img, 0, 0);
}
