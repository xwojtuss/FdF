/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:04:02 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/15 15:30:11 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "vectors.h"

void	calculate_point(t_point *p, t_map_info *map, t_point og)
{
	float	rad_x;
	float	rad_y;
	float	rad_z;
	t_point	temp;

	og.x_pos = og.x_pos * ((float)GRID_SPACE_X + map->scale
			* (float)GRID_SPACE_X / ZOOM_FACTOR) / (map->cols - 1)
		+ EMPTY_SPACE_X / 2 - W_WIDTH / 2 - map->scale * (float)GRID_SPACE_X
		/ (ZOOM_FACTOR * 2);
	og.y_pos = og.y_pos * ((float)GRID_SPACE_Y + map->scale
			* (float)GRID_SPACE_Y / ZOOM_FACTOR) / (map->rows - 1)
		+ EMPTY_SPACE_Y / 2 - W_HEIGHT / 2 - map->scale * (float)GRID_SPACE_Y
		/ (ZOOM_FACTOR * 2);
	og.z_pos = og.z_pos * map->height_factor;
	rad_x = (int)map->rotation.x * M_PI / 180.0;
	rad_y = (int)map->rotation.y * M_PI / 180.0;
	rad_z = (int)map->rotation.z * M_PI / 180.0;
	temp.y_pos = og.y_pos * cos(rad_x) - og.z_pos * sin(rad_x);
	temp.z_pos = og.y_pos * sin(rad_x) + og.z_pos * cos(rad_x);
	copy_point((t_point){og.x_pos, temp.y_pos, temp.z_pos, og.color}, &og);
	temp.x_pos = og.x_pos * cos(rad_y) + og.z_pos * sin(rad_y);
	temp.z_pos = -og.x_pos * sin(rad_y) + og.z_pos * cos(rad_y);
	copy_point((t_point){temp.x_pos, og.y_pos, temp.z_pos, og.color}, &og);
	temp.x_pos = og.x_pos * cos(rad_z) - og.y_pos * sin(rad_z);
	temp.y_pos = og.x_pos * sin(rad_z) + og.y_pos * cos(rad_z);
	copy_point((t_point){temp.x_pos, temp.y_pos, og.z_pos, og.color}, &og);
	copy_point(og, p);
}

void	draw_line(t_point p0, t_point p1, t_map_info *map)
{
	t_point	point0;
	t_point	point1;
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		error;
	int		e2;
	int		line_length;
	int		iter;
	int		color;

	calculate_point(&point0, map, p0);
	calculate_point(&point1, map, p1);
	dx = abs((int)point1.x_pos - (int)point0.x_pos);
	sx = ((int)point0.x_pos < (int)point1.x_pos) * 2 - 1;
	dy = -abs((int)point1.y_pos - (int)point0.y_pos);
	sy = ((int)point0.y_pos < (int)point1.y_pos) * 2 - 1;
	line_length = sqrt(pow(dx, 2) + pow(dy, 2));
	error = dx + dy;
	iter = 0;
	while (true)
	{
		if (p0.color > p1.color)
			color = (((1-iter/line_length)*((p0.color >> 16) & 0xFF) + iter/line_length * (p0.color >> 16)) << 16)|(((1-iter/line_length)*((p0.color >> 8) & 0xFF) + iter/line_length * (p0.color >> 8)) << 8)|(((1-iter/line_length)*((p0.color) & 0xFF) + iter/line_length * (p0.color)));
		else
			color = (((1-iter/line_length)*((p1.color >> 16) & 0xFF) + iter/line_length * (p1.color >> 16)) << 16)|(((1-iter/line_length)*((p1.color >> 8) & 0xFF) + iter/line_length * (p1.color >> 8)) << 8)|(((1-iter/line_length)*((p1.color) & 0xFF) + iter/line_length * (p1.color)));
		my_mlx_pixel_put(map, (int)point0.x_pos + W_WIDTH / 2, (int)point0.y_pos
			+ W_HEIGHT / 2, color);
		if ((int)point0.x_pos == (int)point1.x_pos
			&& (int)point0.y_pos == (int)point1.y_pos)
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			error = error + dy;
			point0.x_pos = (int)point0.x_pos + sx;
		}
		if (e2 <= dx)
		{
			error = error + dx;
			point0.y_pos = (int)point0.y_pos + sy;
		}
		iter++;
	}
}

void	render_image(t_map_info *map)
{
	short	y;
	short	x;
	t_point	curr;
	
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			(void)curr;
			copy_point(map->map[y][x], &curr);
			calculate_point(&curr, map, map->map[y][x]);
			my_mlx_pixel_put(map, curr.x_pos + W_WIDTH / 2, curr.y_pos
				+ W_HEIGHT / 2, curr.color);
			if (x != 0)
				draw_line(map->map[y][x], map->map[y][x - 1], map);
			if (y != 0)
				draw_line(map->map[y][x], map->map[y - 1][x], map);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->screen.mlx, map->screen.win,
		map->screen.img.img, 0, 0);
}
