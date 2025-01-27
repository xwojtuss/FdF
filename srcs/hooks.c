/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:27:30 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 13:29:23 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

static void	clamp_rotation(t_map_info *map)
{
	if (map->rotation.x >= 2 * M_PI)
		map->rotation.x -= 2 * M_PI;
	else if (map->rotation.x < 0)
		map->rotation.x += 2 * M_PI;
	if (map->rotation.y >= 2 * M_PI)
		map->rotation.y -= 2 * M_PI;
	else if (map->rotation.y < 0)
		map->rotation.y += 2 * M_PI;
	if (map->rotation.z >= 2 * M_PI)
		map->rotation.z -= 2 * M_PI;
	else if (map->rotation.z < 0)
		map->rotation.z += 2 * M_PI;
}

static bool	check_rotation(int keycode, t_map_info *map)
{
	if (keycode == XK_d)
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
	else
		return (false);
	return (true);
}

static bool	check_rest(int keycode, t_map_info *map)
{
	if (keycode == XK_equal)
		map->scale_factor++;
	else if (keycode == XK_minus && (float)GRID_SPACE_X + map->scale
		* (float)GRID_SPACE_X / ZOOM_FACTOR > 1)
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
		return (false);
	return (true);
}

int	key_hook(int keycode, t_map_info *map)
{
	if (keycode == XK_Escape)
	{
		free_map(map);
		exit(EXIT_SUCCESS);
	}
	else if (check_rotation(keycode, map) || check_rest(keycode, map))
	{
		ft_memset(map->screen.img.addr, '\0', W_HEIGHT
			* map->screen.img.line_length);
		clamp_rotation(map);
		render_image(map);
	}
	return (EXIT_SUCCESS);
}
