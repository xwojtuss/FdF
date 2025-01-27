/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:46:07 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 16:10:23 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_point(t_point srcs, t_point *dest)
{
	dest->x_pos = srcs.x_pos;
	dest->y_pos = srcs.y_pos;
	dest->z_pos = srcs.z_pos;
	dest->color = srcs.color;
}

bool	is_number(char *str)
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

int	get_token_count(char *line)
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
