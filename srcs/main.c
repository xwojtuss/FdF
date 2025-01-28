/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:42:38 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/28 21:52:47 by wkornato         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	map;

	if ((!BONUS && argc != 2) || (BONUS && argc != 3))
		return (ft_printf("Error\nInvalid argument count\n"), EXIT_FAILURE);
	if (BONUS)
		get_anim_type(&map, argv[2]);
	fd = open_file(argv[1]);
	init_map(&map);
	get_map_size(fd, &map);
	reopen_file(&fd, argv[1], &map);
	load_map(fd, &map);
	close(fd);
	init_mlx(&map);
	if (BONUS)
		mlx_loop_hook(map.screen.mlx, render_image, &map);
	else
		render_image(&map);
	mlx_loop(map.screen.mlx);
	free_map(&map);
	return (EXIT_SUCCESS);
}
