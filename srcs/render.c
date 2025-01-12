/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:04:02 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/12 23:47:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "vectors.h"

t_v3	calculate_isometric(t_v3 *vec)
{
	t_v3	result;
	
	result.x = (float)TILE_DIAG / 2 * sqrt(3) * vec->x + (float)TILE_DIAG / 2 * -sqrt(3) * vec->y + W_WIDTH/2;
	result.y = (float)TILE_DIAG / 2 * -1 * vec->x + (float)TILE_DIAG / 2 * -1 * vec->y + (float)TILE_DIAG / 2 * 2 * vec->z + W_HEIGHT;
	result.z = (float)TILE_DIAG / 2 * (float)-1/sqrt(2) * vec->x + (float)TILE_DIAG / 2 * (float)-1/sqrt(2) * vec->y + (float)TILE_DIAG / 2 * (float)-1/sqrt(2) * vec->z + 0;
	return (result);
}

void	render_image(t_map_info *map)
{
	short	y;
	short	x;
	t_v3	pixel;
	void	*curr;
	
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			(void)curr;
			curr = &map->map[y][x];
			pixel = calculate_isometric((t_v3 *)curr);
			if (pixel.x >= 0 && pixel.x < W_WIDTH && pixel.y >= 0 && pixel.y < W_HEIGHT && ((t_point *)curr)->z_pos == 0)
				my_mlx_pixel_put(&map->screen.img, pixel.x, pixel.y, 0xffffff);
			else if (((t_point *)curr)->z_pos == 10)
				my_mlx_pixel_put(&map->screen.img, pixel.x, pixel.y, 0xff0000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->screen.mlx, map->screen.win, map->screen.img.img, 0, 0);
}
