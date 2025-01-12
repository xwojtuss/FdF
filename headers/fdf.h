/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:43:11 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/12 23:47:29 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define W_HEIGHT 900
# define W_WIDTH 1600
# define WINDOW_NAME "FdF"
# ifndef M_PI
#  define M_PI 3.141592653589793
# endif
# define ALPHA 0.6155 // arcsin(tan 30°)
# define BETA 0.7854 // 45°
# define TILE_DIAG 0.5

# define NOT_SET -42

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		w_height;
	int		w_width;
	t_image	img;
}			t_mlx;

typedef struct s_point
{
	float	x_pos;
	float	y_pos;
	float	z_pos;
	int		color;
}			t_point;

typedef struct s_map_info
{
	t_mlx	screen;
	t_point	**map;
	int		cols;
	int		rows;
}			t_map_info;

//	SRCS
//		ERRORS.C

void		perr_fd(char *message, int fd);
void		perr_fd_free(char *message, int fd, char *to_free);
void		err_fd(char *message, int fd);
void		err_fd_free(char *message, int fd, char *to_free);
void		err_map(char *message, t_map_info *map);

//		FILES.C

void		reopen_file(int *fd, char *filename, t_map_info *map);

//		MEMORY.C

void		free_map(t_map_info *map);
bool		alloc_map(t_map_info *map);
void		init_map(t_map_info *map);

//		MLX.C
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
int	close_win(void *context, int exit_code);
void	init_mlx(t_map_info *map);

//		PARSING.C

void		load_map(int fd, t_map_info *map);
void		get_map_size(int fd, t_map_info *map);

//		RENDER.C

void	render_image(t_map_info *map);

#endif
