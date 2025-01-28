/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:50:38 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/28 21:57:10 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	shake_it_off(t_point *p, t_map_info *map)
{
	t_point	temp;

	copy_point(*p, &temp);
	p->x_pos = temp.x_pos + (double)map->max_height / 100
		* sin((double)map->anim.iter / 25 + rand() % map->max_height);
	p->y_pos = temp.y_pos + (double)map->max_height / 100
		* sin((double)map->anim.iter / 25 + rand() % map->max_height);
}

void	animate(t_point *p, t_map_info *map)
{
	if (map->anim.type == XYSINE)
		p->z_pos = p->z_pos + (double)map->max_height / 2
			* sin((double)map->anim.iter / 25 + map->anim.x * map->scale
				+ map->anim.y * map->scale);
	else if (map->anim.type == XSINE)
		p->z_pos = p->z_pos + (double)map->max_height / 2
			* sin((double)map->anim.iter / 25 + map->anim.x * map->scale);
	else if (map->anim.type == YSINE)
		p->z_pos = p->z_pos + (double)map->max_height / 2
			* sin((double)map->anim.iter / 25 + map->anim.y * map->scale);
	else if (map->anim.type == WATER)
		p->y_pos += 10 * sin(map->anim.x * map->scale + (double)map->anim.iter
				/ 50);
	else if (map->anim.type == RIPPLE)
		p->z_pos += (double)map->max_height / 10 * sin(sqrt(pow(p->x_pos
						- map->cols / 20, 2) + pow(p->y_pos - map->rows / 20,
						2)) * map->scale / 4 - (double)map->anim.iter / 10);
	else if (map->anim.type == WIND)
		p->z_pos += (double)map->max_height / 20 * (sin(p->x_pos * map->scale
					/ 10 + (double)map->anim.iter / 25) + cos(p->y_pos
					* map->scale / 10 + (double)map->anim.iter / 25));
	else if (map->anim.type == SHAKY)
		shake_it_off(p, map);
}

void	get_anim_type(t_map_info *map, char *str)
{
	srand(time(NULL));
	if (!ft_strcmp(str, "xysine") || !ft_strcmp(str, "XYSINE"))
		map->anim.type = XYSINE;
	else if (!ft_strcmp(str, "xsine") || !ft_strcmp(str, "XSINE"))
		map->anim.type = XSINE;
	else if (!ft_strcmp(str, "ysine") || !ft_strcmp(str, "YSINE"))
		map->anim.type = YSINE;
	else if (!ft_strcmp(str, "water") || !ft_strcmp(str, "WATER"))
		map->anim.type = WATER;
	else if (!ft_strcmp(str, "ripple") || !ft_strcmp(str, "RIPPLE"))
		map->anim.type = RIPPLE;
	else if (!ft_strcmp(str, "wind") || !ft_strcmp(str, "WIND"))
		map->anim.type = WIND;
	else if (!ft_strcmp(str, "shaky") || !ft_strcmp(str, "SHAKY"))
		map->anim.type = SHAKY;
	else
	{
		ft_printf("Error\nUnknown animation type\n");
		exit(EXIT_FAILURE);
	}
}
