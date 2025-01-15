/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:31:43 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/15 11:51:30 by wkornato         ###   ########.fr       */
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
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	load_row(t_map_info *map, int idx, int n, char *line)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_strtok_r(line, " ", &line);
	while (token && i < n)
	{
		if (!is_number(token))
			return (false);
		map->map[idx][i].x_pos = i;
		map->map[idx][i].y_pos = idx;
		map->map[idx][i].z_pos = ft_atoi(token);
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
