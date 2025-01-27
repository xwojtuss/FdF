/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:31:43 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 16:16:42 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_cords(t_map_info *map, int idx, int i, char *inner_token)
{
	map->map[idx][i].z_pos = ft_atoi(inner_token);
	map->map[idx][i].x_pos = i;
	map->map[idx][i].y_pos = idx;
	if (map->map[idx][i].z_pos > map->max_height)
		map->max_height = (int)map->map[idx][i].z_pos;
	if (map->map[idx][i].z_pos < map->min_height)
		map->min_height = (int)map->map[idx][i].z_pos;
}

static void	set_color(t_map_info *map, int idx, int i, char *inner_token)
{
	map->map[idx][i].color = NOT_SET;
	if (inner_token)
	{
		map->map[idx][i].color = get_hex(inner_token);
		map->is_color = true;
	}
	else
		map->map[idx][i].color = 0xffffff;
}

static bool	load_row(t_map_info *map, int idx, int n, char *line)
{
	char	*token;
	char	*inner_token;
	char	*inner_saveptr;
	int		i;

	i = 0;
	inner_saveptr = NULL;
	token = ft_strtok_r(line, " ", &line);
	while (token && i < n)
	{
		inner_token = ft_strtok_r(token, ",", &inner_saveptr);
		if (!is_number(inner_token))
			return (false);
		set_cords(map, idx, i, inner_token);
		inner_token = ft_strtok_r(NULL, ",", &inner_saveptr);
		set_color(map, idx, i, inner_token);
		if (map->map[idx][i].color == NOT_SET)
			return (false);
		i++;
		token = ft_strtok_r(NULL, " ", &line);
	}
	if (token || i != n)
		return (false);
	return (true);
}

void	load_map(int fd, t_map_info *map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!load_row(map, i, map->cols, line))
		{
			free_map(map);
			err_fd_free("Invalid map", fd, line);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
}

void	get_map_size(int fd, t_map_info *map)
{
	char	*line;

	line = get_next_line(fd);
	if (line && line[0] != '\n' && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map->cols = get_token_count(line);
	if (map->cols == 0)
		err_fd_free("Invalid map", fd, line);
	while (line)
	{
		(map->rows)++;
		free(line);
		line = get_next_line(fd);
	}
	if (!alloc_map(map))
		perr_fd_free("ft_calloc", fd, line);
}
