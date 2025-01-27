/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:43:11 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 16:31:34 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "vectors.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define W_HEIGHT 900
# define W_WIDTH 1600
// # define EMPTY_SPACE_X W_WIDTH / 5 * W_HEIGHT / W_WIDTH
# define EMPTY_SPACE_X 180
// # define EMPTY_SPACE_Y W_HEIGHT / 5
# define EMPTY_SPACE_Y 180
// # define GRID_SPACE_X (W_WIDTH - 1 - EMPTY_SPACE_X)
# define GRID_SPACE_X 1419
// # define GRID_SPACE_Y (W_HEIGHT - 1 - EMPTY_SPACE_Y)
# define GRID_SPACE_Y 719
# define WINDOW_NAME "FdF"
# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

# define ZOOM_FACTOR 20
// # define ROTATION_STEP 5 * M_PI / 180.0
# define ROTATION_STEP 0.08726
# define TRANSLATION_STEP 10
# define HEIGHT_STEP 0.1

# ifndef BONUS
#  define BONUS 0
# endif

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
	t_v3f	rotation;
	t_v3i	translation;
	float	scale;
	int		scale_factor;
	int		height_factor;
	int		cols;
	int		rows;
	int		min_height;
	int		max_height;
	bool	is_color;
}			t_map_info;

//	SRCS

//		DRAW_LINE.C

void		draw_line(t_point p0, t_point p1, t_map_info *map);

//		ERRORS.C

void		perr_fd(char *message, int fd);
void		perr_fd_free(char *message, int fd, char *to_free);
void		err_fd(char *message, int fd);
void		err_fd_free(char *message, int fd, char *to_free);
void		err_map(char *message, t_map_info *map);

//		FILES.C

void		reopen_file(int *fd, char *filename, t_map_info *map);

//		HOOKS.C

int			key_hook(int keycode, t_map_info *map);

//		MEMORY.C

void		free_map(t_map_info *map);
bool		alloc_map(t_map_info *map);
void		init_map(t_map_info *map);

//		MLX.C
void		my_mlx_pixel_put(t_map_info *map, int x, int y, int color);
int			close_win(void *context, int exit_code);
void		init_mlx(t_map_info *map);

//		PARSING.C

void		load_map(int fd, t_map_info *map);
void		get_map_size(int fd, t_map_info *map);

//		RENDER.C

void		calculate_point(t_point *p, t_map_info *map, t_point og);
void		render_image(t_map_info *map);

//		UTILS.C

void		copy_point(t_point srcs, t_point *dest);
int			get_hex(char *str);
bool		is_number(char *str);
int			get_token_count(char *line);

#endif
