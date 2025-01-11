/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:42:38 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/11 18:44:22 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define LINE_SIZE 5

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

void	perr_fd(char *message, int fd);
void	err_fd(char *message, int fd);

void	get_map_size(int fd, size_t *height, size_t *width)
{
	char	*line;

	line = get_next_line(fd);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	*width = ft_strlen(line);//have to use strtok instead TODO!
	if (*width == 0)
		err_fd_free("Invalid map", fd, line);
	*height = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (*width != ft_strlen(line) || *width % 2 == 0)
			err_fd_free("Invalid map", fd, line);
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	*width = (*width + 1) / 2;
}

int	main(int argc, char **argv)
{
	int	fd;
	size_t	width;
	size_t	height;

	if (argc != 2)
		return (ft_printf("Error\nInvalid argument count\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nCould not open file\n"), EXIT_FAILURE);
	width = 0;
	height = 0;
	(void)height;
	(void)width;
	get_map_size(fd, &height, &width);
	printf("height: %li, width: %li\n", height, width);
	close(fd);
	return (EXIT_SUCCESS);
}
