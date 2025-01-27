/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:42:38 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 13:43:29 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	map;

	if (argc != 2)
		return (ft_printf("Error\nInvalid argument count\n"), EXIT_FAILURE);
	if (ft_strlen(argv[1]) < 4 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4,
			".fdf"))
		return (ft_printf("Error\nInvalid file extension\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), EXIT_FAILURE);
	init_map(&map);
	get_map_size(fd, &map);
	reopen_file(&fd, argv[1], &map);
	load_map(fd, &map);
	close(fd);
	init_mlx(&map);
	render_image(&map);
	mlx_loop(map.screen.mlx);
	free_map(&map);
	return (EXIT_SUCCESS);
}
