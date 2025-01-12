/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:38:12 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/12 22:01:45 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reopen_file(int *fd, char *filename, t_map_info *map)
{
	close(*fd);
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		free_map(map);
		perror("open");
		exit(EXIT_FAILURE);
	}
}
