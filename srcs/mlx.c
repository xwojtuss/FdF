/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:39:14 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/24 13:22:42 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>

void	my_mlx_pixel_put(t_map_info *map, int x, int y, int color)
{
	char	*dst;

	if (x >= map->screen.w_width || x < 0 || y > map->screen.w_height || y < 0)
		return ;
	dst = map->screen.img.addr + (y * map->screen.img.line_length + x
			* (map->screen.img.bits_per_pixel / 8));
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

void	clamp_rotation(t_map_info *map)
{
	if (map->rotation.x >= 360)
		map->rotation.x -= 360;
	else if (map->rotation.x < 0)
		map->rotation.x += 360;
	if (map->rotation.y >= 360)
		map->rotation.y -= 360;
	else if (map->rotation.y < 0)
		map->rotation.y += 360;
	if (map->rotation.z >= 360)
		map->rotation.z -= 360;
	else if (map->rotation.z < 0)
		map->rotation.z += 360;
}

int	key_hook(int keycode, t_map_info *map)
{
	if (keycode == XK_Escape)
	{
		free_map(map);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == XK_d)
		map->rotation.y += ROTATION_STEP;
	else if (keycode == XK_a)
		map->rotation.y -= ROTATION_STEP;
	else if (keycode == XK_w)
		map->rotation.x -= ROTATION_STEP;
	else if (keycode == XK_s)
		map->rotation.x += ROTATION_STEP;
	else if (keycode == XK_q)
		map->rotation.z -= ROTATION_STEP;
	else if (keycode == XK_e)
		map->rotation.z += ROTATION_STEP;
	else if (keycode == XK_equal)
		map->scale_factor++;
	else if (keycode == XK_minus && (float)GRID_SPACE_X + map->scale * (float)GRID_SPACE_X/ZOOM_FACTOR > 1)
		map->scale_factor--;
	else if (keycode == XK_0)
		map->height_factor++;
	else if (keycode == XK_9)
		map->height_factor--;
	else if (keycode == XK_Right)
		map->translation.x += TRANSLATION_STEP;
	else if (keycode == XK_Left)
		map->translation.x -= TRANSLATION_STEP;
	else if (keycode == XK_Up)
		map->translation.y -= TRANSLATION_STEP;
	else if (keycode == XK_Down)
		map->translation.y += TRANSLATION_STEP;
	else
		return (EXIT_SUCCESS);
	ft_memset(map->screen.img.addr, '\0', W_HEIGHT
		* map->screen.img.line_length);
	clamp_rotation(map);
	render_image(map);
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
	mlx_hook(map->screen.win, DestroyNotify, NoEventMask, close_win_handler,
		map);
	mlx_hook(map->screen.win, KeyPress, KeyPressMask, key_hook, map);
}
