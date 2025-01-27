/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:44:03 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 13:44:49 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	calculate_color(t_point p0, t_point p1, int iter, int line_length)
{
	return (((int)((1 - (float)iter / line_length) * ((p0.color >> 16) & 0xFF)
			+ ((float)iter / line_length)
			* ((p1.color >> 16) & 0xFF)) << 16) | ((int)((1 - (float)iter
				/ line_length) * ((p0.color >> 8) & 0xFF) + ((float)iter
				/ line_length)
			* ((p1.color >> 8) & 0xFF)) << 8) | (int)((((1 - (float)iter
					/ line_length) * (p0.color & 0xFF)) + ((float)iter
				/ line_length) * (p1.color & 0xFF))));
}

static void	line_helper(int *error, int *e2, int coords[4], t_point *p0)
{
	*e2 = 2 * *error;
	if (*e2 >= coords[2])
	{
		*error = *error + coords[2];
		p0->x_pos = (int)p0->x_pos + coords[1];
	}
	if (*e2 <= coords[0])
	{
		*error = *error + coords[0];
		p0->y_pos = (int)p0->y_pos + coords[3];
	}
}

void	draw_line(t_point p0, t_point p1, t_map_info *map)
{
	int	coords[4];
	int	error;
	int	e2;
	int	line_length;
	int	iter;

	calculate_point(&p0, map, p0);
	calculate_point(&p1, map, p1);
	coords[0] = abs((int)p1.x_pos - (int)p0.x_pos);
	coords[1] = ((int)p0.x_pos < (int)p1.x_pos) * 2 - 1;
	coords[2] = -abs((int)p1.y_pos - (int)p0.y_pos);
	coords[3] = ((int)p0.y_pos < (int)p1.y_pos) * 2 - 1;
	line_length = sqrt(pow(coords[0], 2) + pow(coords[2], 2));
	error = coords[0] + coords[2];
	iter = 0;
	while (true)
	{
		my_mlx_pixel_put(map, (int)p0.x_pos + W_WIDTH / 2 + map->translation.x,
			(int)p0.y_pos + W_HEIGHT / 2 + map->translation.y,
			calculate_color(p0, p1, iter, line_length));
		if ((int)p0.x_pos == (int)p1.x_pos && (int)p0.y_pos == (int)p1.y_pos)
			break ;
		line_helper(&error, &e2, coords, &p0);
		iter++;
	}
}
