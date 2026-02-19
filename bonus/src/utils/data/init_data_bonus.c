/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "parse_bonus.h"
#include "player_bonus.h"
#include "render_bonus.h"
#include <stdlib.h>

static void	init_textures(t_game *game) {
  game->txt_no = NULL;
  game->txt_so = NULL;
  game->txt_ea = NULL;
  game->txt_we = NULL;
  game->txt_door = NULL;
  game->txt_exit = NULL;
  game->e_txt_s = NULL;
  game->e_txt_w1 = NULL;
  game->e_txt_w2 = NULL;
}

static void	init_allowed_chars(t_game *game) {
  char *default_allowed;
  int i;
  int len;

  default_allowed = " 01NSEWAC\n\t";
  i = 0;
  while (default_allowed[i])
    i++;
  len = i;
  i = 0;
  while (default_allowed[i]) {
    game->allowed_chars[i] = default_allowed[i];
    i++;
  }
  game->allowed_count = len;
  game->allowed_chars[len] = '\0';
}

t_game	*init_data(void) {
  t_game *game;

  game = malloc(sizeof(t_game));
  if (!game) {
    ft_fprintf(2, RED "Error: Malloc failed\n" RESET);
    exit(EXIT_FAILURE);
  }
  init_textures(game);
  init_allowed_chars(game);
  init_keys(game);
  game->sprites = NULL;
  game->enemies = NULL;
  game->floor_color = -1;
  game->ceiling_color = -1;
  game->map.grid = NULL;
  game->map.width = 0;
  game->map.height = 0;
  game->zbuffer = malloc(sizeof(double) * WIN_W);
  if (!game->zbuffer) {
    free(game);
    ft_fprintf(2, RED "Error: Malloc failed (zbuffer)\n" RESET);
    exit(EXIT_FAILURE);
  }
  game->mouse_captured = 0;
  game->finished = 0;
  game->score = 0;
  return (game);
}
