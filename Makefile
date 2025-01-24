CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O3

HEADERS = headers/fdf.h
INCLUDES = -Iheaders -Ilibs/mlx_linux -Ilibs/libft
LIBFT = libs/libft/libft.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
LIBFT_REPO = https://github.com/xwojtuss/Libft.git
MINILIBX = libs/mlx_linux/libmlx.a
LIBS = ${LIBFT} ${MINILIBX} -lm -lX11 -lXext

NAME = fdf

SRCS = main.c errors.c memory.c parsing.c files.c mlx.c render.c debug.c vectors.c utils.c

MAPS = ${wildcard maps/*.fdf}

SRCS_FILES = $(addprefix srcs/, ${SRCS})

OBJS = ${SRCS_FILES:.c=.o}

all: ${NAME} ${NAME_BONUS}

${NAME}: ${LIBFT} ${MINILIBX} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} ${INCLUDES}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

$(SRCSB_DIR)/%.o: $(SRCSB_DIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

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
	rm -f ${OBJS} ${OBJSB}
	make -C libs/libft clean
	make -C libs/mlx_linux clean

fclean:
	rm -f ${OBJS} ${OBJSB}
	rm -f ${NAME} ${NAME_BONUS}
	rm -dfr libs/mlx_linux
	rm -dfr libs/libft

test: all
	@$(foreach MAP, ${MAPS}, \
		clear && cat ${MAP} && ./${NAME} ${MAP};)

re: fclean all

remove_objects:
	rm -f ${OBJS} ${OBJSB}

again: remove_objects all

.PHONY: all clean fclean test re again remove_objects