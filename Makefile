NAME = cub3D

CC = gcc

SAN = -g -fsanitize=address

MLX = mlx

MLX_SRC = ./mlx/libmlx.dylib

MLX_DEST = ./srcs/libmlx.dylib

LIBFT = libft

LIBFT_SRC = ./libft/libft.a

LIBFT_DEST = ./srcs/libft.a

CFLAGS = -Wall -Wextra -Werror -O2

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

HEADER = ./srcs/cub3d.h

FILES = cub3d.c \
			init_utils.c \
			parser.c \
			colors.c \
			direction.c \
			draw_loop.c \
			exit.c \
			exit_utils.c \
			init.c \
			keys.c \
			parse_params.c \
			parse_params_utils.c \
			parser_utils.c \
			screenshot.c \
			sprites.c \
			sprites_utils.c \
			wall_cast.c \
			wall_cast_utils.c \
			check_walls.c

SRCS_DIR = srcs

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	cp $(LIBFT_SRC) $(LIBFT_DEST)
	make -C $(MLX)
	cp $(MLX_SRC) $(MLX_DEST)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT_DEST)

clean:
	make -C $(LIBFT) clean
	make -C $(MLX) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT_DEST) $(MLX_DEST)
	rm -f screenshot.bmp

re: fclean all

.PHONY: clean fclean all re
