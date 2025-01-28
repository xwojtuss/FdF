CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O3

HEADERS = headers/fdf.h headers/animation.h
INCLUDES = -Iheaders -Ilibs/mlx_linux -Ilibs/libft
LIBFT = libs/libft/libft.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
LIBFT_REPO = https://github.com/xwojtuss/Libft.git
MINILIBX = libs/mlx_linux/libmlx.a
LIBS = ${LIBFT} ${MINILIBX} -lm -lX11 -lXext

NAME = fdf

NAME_BONUS = fdf_bonus

SRCS = main.c errors.c memory.c parsing.c files.c mlx.c \
	render.c vectors.c hooks.c draw_line.c utils.c

SRCS_BONUS = animate_bonus.c ${SRCS}

MAPS = ${wildcard maps/*.fdf}

SRCS_FILES = $(addprefix srcs/, ${SRCS})
SRCS_FILES_BONUS = $(addprefix srcs/, ${SRCS_BONUS})

OBJS = ${SRCS_FILES:.c=.o}
OBJS_BONUS = ${SRCS_FILES_BONUS:.c=_bonus.o}

all: ${NAME} ${NAME_BONUS}

bonus: ${NAME_BONUS}

${NAME_BONUS}: ${LIBFT} ${MINILIBX} ${OBJS_BONUS}
	${CC} ${CFLAGS} -DBONUS=1 -o ${NAME_BONUS} ${OBJS_BONUS} ${LIBS} ${INCLUDES}

${NAME}: ${LIBFT} ${MINILIBX} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} ${INCLUDES}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

%_bonus.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -DBONUS=1 -c $< -o $@ ${INCLUDES}

${LIBFT}:
	@if [ ! -d libs/libft ]; then \
		git clone ${LIBFT_REPO} libs/libft; \
	fi
	make -C libs/libft

${MINILIBX}:
	@if [ ! -d libs/mlx_linux ]; then \
		git clone ${MLX_REPO} libs/mlx_linux; \
		cd libs/mlx_linux; \
		bash configure; \
	fi
	make -C libs/mlx_linux

clean:
	rm -f ${OBJS} ${OBJS_BONUS}
	make -C libs/libft clean
	make -C libs/mlx_linux clean

fclean:
	rm -f ${OBJS} ${OBJS_BONUS}
	rm -f ${NAME} ${NAME_BONUS}
	rm -dfr libs/mlx_linux
	rm -dfr libs/libft

test: all
	@$(foreach MAP, ${MAPS}, \
		clear && cat ${MAP} && ./${NAME} ${MAP};)

re: fclean all

remove_objects:
	rm -f ${OBJS} ${OBJS_BONUS}

again: remove_objects all

.PHONY: all clean fclean test re again remove_objects