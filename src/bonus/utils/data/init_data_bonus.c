/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/05 22:16:24 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static const char	g_allowed_chars[] = " 01NSEWDX\n\t";
static const int	g_default_floor_color = -1;
static const int	g_default_ceiling_color = -1;

static void	init_textures(t_game *game)
{
	game->txt_no = NULL;
	game->txt_so = NULL;
	game->txt_ea = NULL;
	game->txt_we = NULL;
	game->txt_door = NULL;
	game->e_txt_s = NULL;
	game->e_txt_w1 = NULL;
	game->e_txt_w2 = NULL;
}

static void	init_entities(t_game *game)
{
	game->sprites = NULL;
	game->enemies = NULL;
}

static void	init_colors(t_game *game)
{
	game->floor_color = g_default_floor_color;
	game->ceiling_color = g_default_ceiling_color;
}

static void	init_map_data(t_game *game)
{
	game->map = NULL;
}

static void	init_allowed_chars(t_game *game)
{
	int	i;
	int	len;

	len = (int)(sizeof(g_allowed_chars) - 1);
	game->allowed_count = 0;
	i = 0;
	while (i < len)
	{
		game->allowed_chars[i] = g_allowed_chars[i];
		i++;
	}
	game->allowed_count = len;
	game->allowed_chars[len] = '\0';
}

t_game	*init_data(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_fprintf(2, RED "Error: Malloc failed\n" RESET);
		exit(EXIT_FAILURE);
	}
	init_textures(game);
	init_entities(game);
	init_colors(game);
	init_map_data(game);
	init_allowed_chars(game);
	return (game);
}
