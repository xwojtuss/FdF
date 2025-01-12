/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:39:14 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/12 22:02:08 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_win(void *context, int exit_code)
{
	t_map_info	*map;

	map = (t_map_info *)context;
	if (map->screen.img.img && map->screen.mlx)
		mlx_destroy_image(map->screen.mlx, map->screen.img.img);
	if (map->screen.win && map->screen.mlx)
		mlx_destroy_window(map->screen.mlx, map->screen.win);
	if (map->screen.mlx)
		mlx_destroy_display(map->screen.mlx);
	if (map->screen.mlx)
		free(map->screen.mlx);
	if (exit_code != NOT_SET)
		exit(exit_code);
	return (0);
}

int	close_win_handler(void *context)
{
	t_map_info	*map;

	map = (t_map_info *)context;
	free_map(map);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_map_info *map)
{
	if (keycode == XK_Escape)
	{
		free_map(map);
		exit(EXIT_SUCCESS);
	}
	// render scene again
	return (EXIT_SUCCESS);
}


void	init_mlx(t_map_info *map)
{
	map->screen.mlx = mlx_init();
	if (!map->screen.mlx)
		err_map("Could not initialize mlx", map);
	map->screen.win = mlx_new_window(map->screen.mlx, map->screen.w_width,
			map->screen.w_height, WINDOW_NAME);
	if (!map->screen.win)
		err_map("Could not create window", map);
	map->screen.img.img = mlx_new_image(map->screen.mlx, map->screen.w_width,
			map->screen.w_height);
	if (!map->screen.img.img)
		err_map("Could not create image", map);
	map->screen.img.addr = mlx_get_data_addr(map->screen.img.img,
			&map->screen.img.bits_per_pixel, &map->screen.img.line_length,
			&map->screen.img.endian);
	if (!map->screen.img.addr)
		err_map("Could not get image address", map);
	mlx_hook(map->screen.win, DestroyNotify, NoEventMask, close_win_handler, map);
	mlx_hook(map->screen.win, KeyPress, KeyPressMask, key_hook, map);
}
