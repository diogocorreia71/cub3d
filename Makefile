# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 14:34:42 by jmarinho          #+#    #+#              #
#    Updated: 2024/06/25 18:33:21 by jmarinho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

NAME = cub3D

SRC_PATH = src/
VPATH = $(SRC_PATH) $(SRC_PATH)parser $(SRC_PATH)events $(SRC_PATH)sprites
SRC = main.c parser_utils.c check_b4_init.c copy_config_map.c copy_game_map.c \
	check_game_map.c make_game.c image.c sprite_utils.c hooks.c raycasting.c \
	movements.c copy_config_map_aux.c flood_fill_and_counters.c \

OBJ_PATH = obj/
OBJFILES = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJFILES))

CC = cc

MLX_HEADER = -I minilibx
MLX_PATH = minilibx-linux
LIBFT_PATH = libft

CFLAGS = -Wall -Wextra -Werror -I include
MLXFLAGS = -Lminilibx-linux -lmlx -lXext -lX11
LIBFTFLAGS = -Llibft -lft
MATHFLAGS = -lm

all: $(NAME)

$(NAME):	$(OBJ)
			@make -C $(MLX_PATH) > /dev/null 2>&1
			@echo "$(GREEN)MLX Compiled$(RESET)"
			@make -C $(LIBFT_PATH) > /dev/null
			@echo "$(GREEN)Libft Compiled$(RESET)"
			@$(CC) -o $(NAME) $(OBJ) $(MLXFLAGS) $(LIBFTFLAGS) $(MATHFLAGS)
			@echo "$(GREEN)Cub3d Compiled$(RESET)"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(MLX_HEADER) -c $< -o $@

clean:
		@make clean -C $(LIBFT_PATH) > /dev/null
		@make clean -C $(MLX_PATH) > /dev/null 2>&1
		@rm -rf $(OBJ) > /dev/null

fclean: clean
		@make fclean -C  $(LIBFT_PATH) > /dev/null
		@rm -f $(NAME)
		@echo "$(GREEN)Objects cleaned$(RESET)"

re: fclean all