# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 13:45:00 by agarcia           #+#    #+#              #
#    Updated: 2025/12/18 00:19:35 by agarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

SRC_DIR		:= src
SRCS		:= 	$(SRC_DIR)/main.c \
				$(SRC_DIR)/error.c \
 				$(SRC_DIR)/init.c \
 				$(SRC_DIR)/map_utils/map_parser.c \
 				$(SRC_DIR)/map_utils/map_validation.c \
 				$(SRC_DIR)/map_utils/map_memory.c \
				
OBJS_DIR	:= objs
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJS_DIR)/%.o)

# -------------- LIBS -------------- #
LIBS_DIR	:= ./libs
GNL_DIR		:= $(LIBS_DIR)/gnl
GNL_LIB		:= $(GNL_DIR)/libgnl.a
LIBFT_DIR	:= $(LIBS_DIR)/libft
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a
# ---------------------------------- #

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I includes -c $< -o $@

$(GNL_LIB):
	@make -C $(GNL_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(GNL_LIB) $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_LIB) $(LIBFT_LIB) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	@make -C $(GNL_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(GNL_DIR) fclean
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
