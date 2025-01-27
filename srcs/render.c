/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:04:02 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 13:55:19 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "vectors.h"

void	calculate_point(t_point *p, t_map_info *map, t_point og)
{
	t_point	temp;

	og.x_pos = (og.x_pos - map->cols / 2) * map->scale * 40;
	og.y_pos = (og.y_pos - map->rows / 2) * map->scale * 40;
	og.z_pos = og.z_pos * ((float)map->height_factor * HEIGHT_STEP) * (2
			+ map->scale * 3);
	temp.y_pos = og.y_pos * cos(map->rotation.x) - og.z_pos
		* sin(map->rotation.x);
	temp.z_pos = og.y_pos * sin(map->rotation.x) + og.z_pos
		* cos(map->rotation.x);
	temp.x_pos = og.x_pos;
	og.x_pos = temp.x_pos * cos(map->rotation.y) + temp.z_pos
		* sin(map->rotation.y);
	og.z_pos = -temp.x_pos * sin(map->rotation.y) + temp.z_pos
		* cos(map->rotation.y);
	og.y_pos = temp.y_pos;
	temp.x_pos = og.x_pos * cos(map->rotation.z) - og.y_pos
		* sin(map->rotation.z);
	temp.y_pos = og.x_pos * sin(map->rotation.z) + og.y_pos
		* cos(map->rotation.z);
	temp.z_pos = og.z_pos;
	copy_point((t_point){temp.x_pos, temp.y_pos, temp.z_pos, og.color}, p);
}

void	display_point(int x, int y, t_map_info *map)
{
	if (!map->is_color && map->max_height != map->min_height)
		map->map[y][x].color = 0xffffff * (1
				- ((float)(map->map[y][x].z_pos - map->min_height)
					/ (map->max_height - map->min_height) / 2) + 0.5);
	if (x != 0)
		draw_line(map->map[y][x], map->map[y][x - 1], map);
	if (y != 0)
		draw_line(map->map[y][x], map->map[y - 1][x], map);
}

void	render_normal(t_map_info *map)
{
	short	y;
	short	x;

	x = 0;
	while (x < map->cols)
	{
		y = 0;
		while (y < map->rows)
		{
			display_point(x, y, map);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(map->screen.mlx, map->screen.win,
		map->screen.img.img, 0, 0);
}

void	render_reverse(t_map_info *map)
{
	short	y;
	short	x;

	x = map->cols - 1;
	while (x >= 0)
	{
		y = map->rows - 1;
		while (y >= 0)
		{
			display_point(x, y, map);
			y--;
		}
		x--;
	}
	mlx_put_image_to_window(map->screen.mlx, map->screen.win,
		map->screen.img.img, 0, 0);
}

void	render_image(t_map_info *map)
{
	if (map->cols > map->rows)
		map->scale = W_HEIGHT / (map->cols * 40.0f + 40.0f) * (1
				+ (float)map->scale_factor / 50);
	else
		map->scale = W_HEIGHT / (map->rows * 40.0f + 40.0f) * (1
				+ (float)map->scale_factor / 50);
	if ((map->rotation.y <= 0 && map->rotation.y >= -M_PI / 2)
		|| (map->rotation.y >= M_PI && map->rotation.y <= 2 * M_PI))
		render_normal(map);
	else
		render_reverse(map);
}
