# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 13:45:00 by agarcia           #+#    #+#              #
#    Updated: 2025/12/18 15:23:19 by adriescr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

SRC_DIR		:= src
DATA_DIR	:= $(SRC_DIR)/data
UTILS_DIR	:= $(SRC_DIR)/utils

SRCS_DATA	:= 	$(DATA_DIR)/init_data.c \
				${DATA_DIR}/read_data.c

SRCS_UTILS	:=	${UTILS_DIR}/clear_game.c \
				${UTILS_DIR}/parse_rgb.c \
				${UTILS_DIR}/print/ft_error.c \
				${UTILS_DIR}/print/ft_putstr_fd_color.c \
				${UTILS_DIR}/print/ft_putcolor.c \
				$(UTILS_DIR)/map/map_parser.c \
 				$(UTILS_DIR)/map/map_validation.c \
 				$(UTILS_DIR)/map/map_memory.c \

SRCS		:= 	$(SRC_DIR)/main.c \
 				$(SRC_DIR)/init_mlx.c \
				$(SRCS_DATA) \
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
	$(CC) $(CFLAGS) -I includes -c $< -o $@

$(GNL_LIB):
	@if [ -d "$(GNL_DIR)" ]; then $(MAKE) -C $(GNL_DIR); else echo "Warning: $(GNL_DIR) not found, skipping gnl build"; fi

$(LIBFT_LIB):
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR); else echo "Warning: $(LIBFT_DIR) not found, skipping libft build"; fi

$(MLX_LIB):
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR); else echo "Warning: $(MLX_DIR) not found, skipping mlx build"; fi

$(NAME): $(GNL_LIB) $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; else echo "Warning: $(MLX_DIR) not found, skipping mlx clean"; fi
	rm -rf $(OBJS_DIR)
	@if [ -d "$(GNL_DIR)" ]; then $(MAKE) -C $(GNL_DIR) clean; else echo "Warning: $(GNL_DIR) not found, skipping gnl clean"; fi
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; else echo "Warning: $(LIBFT_DIR) not found, skipping libft clean"; fi

fclean: clean
	rm -f $(NAME)
	@if [ -d "$(GNL_DIR)" ]; then $(MAKE) -C $(GNL_DIR) fclean; else echo "Warning: $(GNL_DIR) not found, skipping gnl fclean"; fi
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) fclean; else echo "Warning: $(LIBFT_DIR) not found, skipping libft fclean"; fi

re: fclean all

.PHONY: all clean fclean re
