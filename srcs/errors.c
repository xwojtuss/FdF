/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:31:46 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/12 21:52:38 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	perr_fd(char *message, int fd)
{
	close(fd);
	perror(message);
	exit(EXIT_FAILURE);
}

void	perr_fd_free(char *message, int fd, char *to_free)
{
	close(fd);
	free(to_free);
	perror(message);
	exit(EXIT_FAILURE);
}
void	err_fd(char *message, int fd)
{
	close(fd);
	ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

void	err_fd_free(char *message, int fd, char *to_free)
{
	close(fd);
	ft_printf("Error\n%s\n", message);
	free(to_free);
	exit(EXIT_FAILURE);
}

void	err_map(char *message, t_map_info *map)
{
	ft_printf("Error\n%s\n", message);
	free_map(map);
	exit(EXIT_FAILURE);
}
