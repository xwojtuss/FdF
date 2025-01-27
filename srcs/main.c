/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:42:38 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 16:36:59 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	open_file(char *filename)
{
	int	fd;

	if (ft_strlen(filename) < 4 || ft_strcmp(filename + ft_strlen(filename)
			- 4, ".fdf"))
	{
		ft_printf("Error\nInvalid file extension\n");
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	text_to_fdf(t_map_info *map, char *text)
{
	(void)map;
	(void)text;
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	map;

	if (argc != 2)
		return (ft_printf("Error\nInvalid argument count\n"), EXIT_FAILURE);
	if (!BONUS)
		fd = open_file(1[argv]);
	init_map(&map);
	if (!BONUS)
	{
		get_map_size(fd, &map);
		reopen_file(&fd, argv[1], &map);
		load_map(fd, &map);
		close(fd);
	}
	else
		text_to_fdf(&map, argv[1]);
	init_mlx(&map);
	render_image(&map);
	mlx_loop(map.screen.mlx);
	free_map(&map);
	return (EXIT_SUCCESS);
}
