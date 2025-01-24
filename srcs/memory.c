/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:31:41 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/24 13:11:57 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map_info *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		free(map->map[i]);
		i++;
	}
	close_win(map, NOT_SET);
	free(map->map);
}

bool	alloc_map(t_map_info *map)
{
	int	i;
	int	j;

	map->map = (t_point **)ft_calloc(sizeof(t_point *), map->rows);
	if (!map->map)
		return (false);
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		map->map[i] = (t_point *)ft_calloc(sizeof(t_point), map->cols);
		if (!map->map[i])
		{
			while (j < i)
			{
				free(map->map[i]);
				j++;
			}
			free(map->map);
			return (false);
		}
		i++;
	}
	return (true);
}

void	init_map(t_map_info *map)
{
	map->cols = 0;
	map->rows = 0;
	map->map = NULL;
	map->screen.img.img = NULL;
	map->screen.mlx = NULL;
	map->screen.win = NULL;
	map->screen.w_height = W_HEIGHT;
	map->screen.w_width = W_WIDTH;
	map->height_factor = 7;
	map->scale_factor = 0;
	map->scale = 1;
	// map->rotation.x = 45;
	// map->rotation.y = -35;
	// map->rotation.z = 30;
	map->rotation.x = 0;
	map->rotation.y = 0;
	map->rotation.z = 0;
	map->translation.x = 0;
	map->translation.y = 0;
	map->translation.z = 0;
	map->max_height = INT_MIN;
	map->min_height = INT_MAX;
	map->is_color = false;
}
