# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 13:45:00 by agarcia           #+#    #+#              #
#    Updated: 2025/12/18 19:06:50 by adriescr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

CC			:= cc
CFLAGS		:=

SRC_DIR		:= src
DATA_DIR	:= $(SRC_DIR)/data
UTILS_DIR	:= $(SRC_DIR)/utils


SRCS_UTILS	:=	${UTILS_DIR}/game/clear_game.c \
				${UTILS_DIR}/game/game_loop.c \
				${UTILS_DIR}/game/player_movement.c \
				${UTILS_DIR}/parse_rgb.c \
				${UTILS_DIR}/print/ft_error.c \
				${UTILS_DIR}/print/ft_putstr_fd_color.c \
				${UTILS_DIR}/print/ft_putcolor.c \
				$(UTILS_DIR)/map/map_parser.c \
 				$(UTILS_DIR)/map/map_validation.c \
 				$(UTILS_DIR)/map/map_memory.c \
				$(UTILS_DIR)/data/init_data.c \
				$(UTILS_DIR)/data/read_data.c \
				$(UTILS_DIR)/mlx/init_mlx.c \
				$(UTILS_DIR)/mlx/image_buffer.c \
				$(UTILS_DIR)/color/color_utils.c \
				$(UTILS_DIR)/player/player_utils.c \
				$(UTILS_DIR)/raycast/dda.c \
				$(UTILS_DIR)/raycast/draw_column.c \
				$(UTILS_DIR)/raycast/init_raycast.c \
				$(UTILS_DIR)/raycast/perpendicular_wall_distance.c \
				$(UTILS_DIR)/raycast/raycast.c \

SRCS		:= 	$(SRC_DIR)/main.c \
				$(SRCS_UTILS) \

OBJS_DIR	:= objs
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJS_DIR)/%.o)

# -------------- LIBS -------------- #
LIBS_DIR	:= ./libs
LIBFT_DIR	:= $(LIBS_DIR)/libft
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a
MLX_DIR		:= $(LIBS_DIR)/mlx
MLX_LIB		:= $(MLX_DIR)/libmlx.a
MLX_FLAGS	:= -framework OpenGL -framework AppKit
# ---------------------------------- #

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I includes -c $< -o $@
	@if [ $$? -ne 0 ]; then \
		echo "\033[31mError durante la compilación de ${NAME}.\033[0m"; \
	fi

$(LIBFT_LIB):
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR); else echo "Warning: $(LIBFT_DIR) not found, skipping libft build"; fi

$(MLX_LIB):
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR); else echo "Warning: $(MLX_DIR) not found, skipping mlx build"; fi

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@if [ $$? -ne 0 ]; then \
		echo "\033[31mError durante la compilación de ${NAME}.\033[0m"; \
	fi

clean:
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; else echo "Warning: $(MLX_DIR) not found, skipping mlx clean"; fi
	@rm -rf $(OBJS_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; else echo "Warning: $(LIBFT_DIR) not found, skipping libft clean"; fi

fclean: clean
	@rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) fclean; else echo "Warning: $(LIBFT_DIR) not found, skipping libft fclean"; fi

re: fclean all

.PHONY: all clean fclean re
