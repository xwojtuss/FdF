/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:31:43 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/16 21:31:08 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_token_count(char *line)
{
	int		count;
	char	*token;
	char	*dup;
	char	*saveptr;

	count = 0;
	if (!line || line[0] == '\n' || line[0] == '\0')
		return (0);
	dup = ft_strdup(line);
	token = ft_strtok_r(dup, " ", &saveptr);
	while (token)
	{
		token = ft_strtok_r(NULL, " ", &saveptr);
		count++;
	}
	free(dup);
	return (count);
}

static bool	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && i != 0)
			return (true);
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (false);
		i++;
	}
	return (true);
}

int	get_hex(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = (result << 4) | ((str[i] - '0') & 0xF);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = (result << 4) | ((str[i] - 'a' + 10) & 0xF);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = (result << 4) | ((str[i] - 'A' + 10) & 0xF);
		i++;
	}
	return (result);
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
		map->map[idx][i].z_pos = ft_atoi(inner_token);
		map->map[idx][i].x_pos = i;
		map->map[idx][i].y_pos = idx;
		if (map->map[idx][i].z_pos > map->max_height)
			map->max_height = (int)map->map[idx][i].z_pos;
		if (map->map[idx][i].z_pos < map->min_height)
			map->min_height = (int)map->map[idx][i].z_pos;
		inner_token = ft_strtok_r(NULL, ",", &inner_saveptr);
		if (inner_token)
		{
			map->map[idx][i].color = get_hex(inner_token);
			map->is_color = true;
		}
		else
			map->map[idx][i].color = 0xffffff;
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
