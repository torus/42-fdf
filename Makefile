#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/13 16:22:39 by thisai            #+#    #+#              #
#    Updated: 2021/01/13 18:07:39 by thisai           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

MLX_DIR = ./minilibx-linux
LIBFT_DIR = ./libft

MLX = $(MLX_DIR)/libmlx.a
FT = $(LIBFT_DIR)/libft.a

SRCS = cub3d.c scene.c map.c utils.c player.c render2.c			\
	scene_parser_map.c scene_parser_storage.c hooks.c hooks2.c	\
	loophook.c render.c

HEADERS = cub3d_int.h cub3d.h scene.h scene_int.h
OBJS = $(SRCS:%.c=%.o)

NAME = fdf

CFLAGS = -I $(MLX_DIR) -I $(LIBFT_DIR) -Wall -Wextra #-Werror
LDFLAGS = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -L $(LIBFT_DIR) -lft

# CFLAGS = -g -fsanitize=address -I $(MLX_DIR) -I $(LIBFT_DIR) -Wall -Wextra -Werror
# LDFLAGS = -fsanitize=address -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -L $(LIBFT_DIR) -lft

all: $(NAME)

bonus: all

$(NAME)	:$(OBJS) $(MLX) $(FT)
	$(CC) -o $(NAME) $^ $(LDFLAGS)

$(MLX):
	cd $(MLX_DIR) && ./configure && make

$(FT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS): $(HEADERS)

clean:
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) *~

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean $(NAME)

run: $(NAME)
	./$(NAME) test/test_maps/42.fdf

run-save: $(NAME)
	valgrind ./$(NAME) test/valid.cub --save

test:
	make -C test/

.PHONY: test clean re run run-save
