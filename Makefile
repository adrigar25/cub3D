# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 13:45:00 by agarcia           #+#    #+#              #
#    Updated: 2026/02/07 00:37:01 by agarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D
NAME_BONUS	:= cub3D_bonus

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

# ============ MANDATORY ============ #
SRC_MAND_DIR	:= ./src/mandatory
UTILS_MAND_DIR	:= $(SRC_MAND_DIR)/utils


SRCS_MAND_UTILS	:=	${UTILS_MAND_DIR}/game/clear_game.c \
					${UTILS_MAND_DIR}/game/game_loop.c \
					${UTILS_MAND_DIR}/game/keys/key_init.c \
					${UTILS_MAND_DIR}/game/keys/key_press.c \
					${UTILS_MAND_DIR}/game/keys/key_release.c \
					${UTILS_MAND_DIR}/game/keys/key_update.c \
					${UTILS_MAND_DIR}/game/movement/move_player.c \
					${UTILS_MAND_DIR}/game/movement/rotate_player.c \
					${UTILS_MAND_DIR}/game/movement/position_validation.c \
					${UTILS_MAND_DIR}/print/ft_error.c \
					${UTILS_MAND_DIR}/print/ft_putstr_fd_color.c \
					${UTILS_MAND_DIR}/print/ft_putcolor.c \
					$(UTILS_MAND_DIR)/map/read_map.c \
					$(UTILS_MAND_DIR)/map/check_map.c \
					$(UTILS_MAND_DIR)/map/check_walls.c \
					$(UTILS_MAND_DIR)/map/check_empty.c \
					$(UTILS_MAND_DIR)/map/check_characters.c \
					$(UTILS_MAND_DIR)/map/check_player.c \
					$(UTILS_MAND_DIR)/data/init_data.c \
					$(UTILS_MAND_DIR)/data/read_data.c \
					$(UTILS_MAND_DIR)/data/check_data.c \
					$(UTILS_MAND_DIR)/mlx/init_mlx.c \
					$(UTILS_MAND_DIR)/mlx/image_buffer.c \
					$(UTILS_MAND_DIR)/color/color_utils.c \
					$(UTILS_MAND_DIR)/color/parse_rgb.c \
					$(UTILS_MAND_DIR)/player/player_utils.c \
					$(UTILS_MAND_DIR)/raycast/dda.c \
					$(UTILS_MAND_DIR)/raycast/draw_column.c \
					$(UTILS_MAND_DIR)/raycast/init_raycast.c \
					$(UTILS_MAND_DIR)/raycast/perpendicular_wall_distance.c \
					$(UTILS_MAND_DIR)/raycast/raycast.c \
					$(UTILS_MAND_DIR)/math/geometry.c \
					$(UTILS_MAND_DIR)/math/camera.c \
					$(UTILS_MAND_DIR)/math/map.c \
					$(UTILS_MAND_DIR)/math/utils_basic.c \
					$(UTILS_MAND_DIR)/math/utils_raycast.c \
					$(UTILS_MAND_DIR)/math/vector.c \

SRCS_MAND	:= 	$(SRC_MAND_DIR)/main.c \
				$(SRCS_MAND_UTILS) \

OBJS_MAND_DIR	:= objs_mandatory
OBJS_MAND		:= $(SRCS_MAND:$(SRC_MAND_DIR)/%.c=$(OBJS_MAND_DIR)/%.o)

# ============ BONUS ============ #
SRC_BONUS_DIR	:= ./src/bonus
UTILS_BONUS_DIR	:= $(SRC_BONUS_DIR)/utils

SRCS_BONUS_UTILS :=	${UTILS_BONUS_DIR}/game/clear_game_bonus.c \
					${UTILS_BONUS_DIR}/game/game_loop_bonus.c \
					${UTILS_BONUS_DIR}/game/keys/key_init_bonus.c \
					${UTILS_BONUS_DIR}/game/keys/key_press_bonus.c \
					${UTILS_BONUS_DIR}/game/keys/key_release_bonus.c \
					${UTILS_BONUS_DIR}/game/keys/key_update_bonus.c \
					${UTILS_BONUS_DIR}/game/keys/mouse_handler_bonus.c \
					${UTILS_BONUS_DIR}/game/movement/move_player_bonus.c \
					${UTILS_BONUS_DIR}/game/movement/rotate_player_bonus.c \
					${UTILS_BONUS_DIR}/game/movement/position_validation_bonus.c \
					${UTILS_BONUS_DIR}/print/ft_error_bonus.c \
					${UTILS_BONUS_DIR}/print/ft_putstr_fd_color_bonus.c \
					${UTILS_BONUS_DIR}/print/ft_putcolor_bonus.c \
					$(UTILS_BONUS_DIR)/map/read_map_bonus.c \
					$(UTILS_BONUS_DIR)/map/check_map_bonus.c \
					$(UTILS_BONUS_DIR)/map/check_walls_bonus.c \
					$(UTILS_BONUS_DIR)/map/check_empty_bonus.c \
					$(UTILS_BONUS_DIR)/map/check_characters_bonus.c \
					$(UTILS_BONUS_DIR)/map/check_player_bonus.c \
					$(UTILS_BONUS_DIR)/minimap/print_minimap_bonus.c \
					$(UTILS_BONUS_DIR)/minimap/player_draw_bonus.c \
					$(UTILS_BONUS_DIR)/minimap/draw_line_bonus.c \
					$(UTILS_BONUS_DIR)/minimap/triangle_helpers_bonus.c \
					$(UTILS_BONUS_DIR)/minimap/fill_triangle_bonus.c \
					$(UTILS_BONUS_DIR)/minimap/minimap_put_image_bonus.c \
					$(UTILS_BONUS_DIR)/data/init_data_bonus.c \
					$(UTILS_BONUS_DIR)/data/read_data_bonus.c \
					$(UTILS_BONUS_DIR)/data/check_data_bonus.c \
					$(UTILS_BONUS_DIR)/mlx/init_mlx_bonus.c \
					$(UTILS_BONUS_DIR)/mlx/image_buffer_bonus.c \
					$(UTILS_BONUS_DIR)/color/color_utils_bonus.c \
					$(UTILS_BONUS_DIR)/color/parse_rgb_bonus.c \
					$(UTILS_BONUS_DIR)/player/player_utils_bonus.c \
					$(UTILS_BONUS_DIR)/raycast/dda_bonus.c \
					$(UTILS_BONUS_DIR)/raycast/draw_column_bonus.c \
					$(UTILS_BONUS_DIR)/raycast/init_raycast_bonus.c \
					$(UTILS_BONUS_DIR)/raycast/perpendicular_wall_distance_bonus.c \
					$(UTILS_BONUS_DIR)/raycast/raycast_bonus.c \
					$(UTILS_BONUS_DIR)/enemy/enemy_create_bonus.c \
					$(UTILS_BONUS_DIR)/enemy/enemy_list_bonus.c \
					$(UTILS_BONUS_DIR)/enemy/enemy_collect_bonus.c \
					$(UTILS_BONUS_DIR)/enemy/enemy_ai_bonus.c \
					$(UTILS_BONUS_DIR)/enemy/enemy_vision_bonus.c \
					$(UTILS_BONUS_DIR)/door/door_utils_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_draw_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_helpers_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_render_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_window_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_count_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_append_bonus.c \
					$(UTILS_BONUS_DIR)/sprite/sprite_lookup_bonus.c \


SRCS_BONUS	:= 	$(SRC_BONUS_DIR)/main_bonus.c \
				$(SRCS_BONUS_UTILS) \

OBJS_BONUS_DIR	:= objs_bonus
OBJS_BONUS		:= $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJS_BONUS_DIR)/%.o)

# -------------- LIBS -------------- #
LIBS_DIR	:= ./libs
LIBFT_DIR	:= $(LIBS_DIR)/libft
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a
MLX_DIR		:= $(LIBS_DIR)/mlx
MLX_LIB		:= $(MLX_DIR)/libmlx.a
MLX_FLAGS	:= -framework OpenGL -framework AppKit
# ---------------------------------- #

# ============ RULES ============ #

all: $(NAME)

bonus: $(NAME_BONUS)

# MANDATORY
$(OBJS_MAND_DIR):
	@mkdir -p $(OBJS_MAND_DIR)
	@mkdir -p $(OBJS_MAND_DIR)/utils/game/keys
	@mkdir -p $(OBJS_MAND_DIR)/utils/game/movement
	@mkdir -p $(OBJS_MAND_DIR)/utils/map
	@mkdir -p $(OBJS_MAND_DIR)/utils/data
	@mkdir -p $(OBJS_MAND_DIR)/utils/mlx
	@mkdir -p $(OBJS_MAND_DIR)/utils/color
	@mkdir -p $(OBJS_MAND_DIR)/utils/player
	@mkdir -p $(OBJS_MAND_DIR)/utils/raycast
	@mkdir -p $(OBJS_MAND_DIR)/utils/print
	@mkdir -p $(OBJS_MAND_DIR)/utils/math
	@mkdir -p $(OBJS_MAND_DIR)/utils/math/geometry
	@mkdir -p $(OBJS_MAND_DIR)/utils/math/map
	@mkdir -p $(OBJS_MAND_DIR)/utils/math/utils
	@mkdir -p $(OBJS_MAND_DIR)/utils/math/vector

$(OBJS_MAND_DIR)/%.o: $(SRC_MAND_DIR)/%.c | $(OBJS_MAND_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@if [ $$? -ne 0 ]; then \
		echo "\033[31mError durante la compilación de ${NAME}.\033[0m"; \
	fi

# BONUS
$(OBJS_BONUS_DIR):
	@mkdir -p $(OBJS_BONUS_DIR)
	@mkdir -p $(OBJS_BONUS_DIR)/utils/game/keys
	@mkdir -p $(OBJS_BONUS_DIR)/utils/game/movement
	@mkdir -p $(OBJS_BONUS_DIR)/utils/map
	@mkdir -p $(OBJS_BONUS_DIR)/utils/minimap
	@mkdir -p $(OBJS_BONUS_DIR)/utils/data
	@mkdir -p $(OBJS_BONUS_DIR)/utils/mlx
	@mkdir -p $(OBJS_BONUS_DIR)/utils/color
	@mkdir -p $(OBJS_BONUS_DIR)/utils/player
	@mkdir -p $(OBJS_BONUS_DIR)/utils/raycast
	@mkdir -p $(OBJS_BONUS_DIR)/utils/print
	@mkdir -p $(OBJS_BONUS_DIR)/utils/door
	@mkdir -p $(OBJS_BONUS_DIR)/utils/sprite
	@mkdir -p $(OBJS_BONUS_DIR)/utils/enemy

$(OBJS_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJS_BONUS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@if [ $$? -ne 0 ]; then \
		echo "\033[31mError durante la compilación de ${NAME_BONUS}.\033[0m"; \
	fi

# LIBS
$(LIBFT_LIB):
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR); else echo "Warning: $(LIBFT_DIR) not found, skipping libft build"; fi

$(MLX_LIB):
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR); else echo "Warning: $(MLX_DIR) not found, skipping mlx build"; fi

# LINKING
$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS_MAND)
	@$(CC) $(CFLAGS) $(SRCS_MAND) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@if [ $$? -ne 0 ]; then \
		echo "\033[31mError durante la compilación de ${NAME}.\033[0m"; \
	else \
		echo "\033[32m✓ ${NAME} compilado correctamente.\033[0m"; \
	fi

$(NAME_BONUS): $(LIBFT_LIB) $(MLX_LIB) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(SRCS_BONUS) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME_BONUS)
	@if [ $$? -ne 0 ]; then \
		echo "\033[31mError durante la compilación de ${NAME_BONUS}.\033[0m"; \
	else \
		echo "\033[32m✓ ${NAME_BONUS} compilado correctamente.\033[0m"; \
	fi

# CLEAN
clean:
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; else echo "Warning: $(MLX_DIR) not found, skipping mlx clean"; fi
	@rm -rf $(OBJS_MAND_DIR) $(OBJS_BONUS_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; else echo "Warning: $(LIBFT_DIR) not found, skipping libft clean"; fi

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) fclean; else echo "Warning: $(LIBFT_DIR) not found, skipping libft fclean"; fi
	# Fallback: eliminar cualquier .o/.a residual en libft
	@if [ -d "$(LIBFT_DIR)" ]; then find "$(LIBFT_DIR)" -type f \( -name "*.o" -o -name "*.a" \) -delete; fi

re: fclean all

.PHONY: all bonus clean fclean re
