/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:08:58 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/22 18:10:20 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"
#include "parse_bonus.h"
#include <unistd.h>

static int	check_sprites(t_game *game)
{
	t_texture	*current;

	current = game->sprites;
	while (current)
	{
		if (!current->path || access(current->path, F_OK) == -1)
		{
			ft_fprintf(2, RED "Error: Sprite texture file");
			if (current->path)
				ft_fprintf(2, " '%s'", current->path);
			ft_fprintf(2, " not found\n" RESET);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

static int	check_texture_file(t_texture *texture, char *label)
{
	if (!texture)
		return ((1));
	if (!texture->path || access(texture->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: %s texture file not found\n" RESET, label);
		return (0);
	}
	return (1);
}

static int	check_colors(t_game *game)
{
	if (game->floor_color == -1 || game->ceiling_color == -1)
	{
		ft_fprintf(2, RED "Error: Missing floor or ceiling color\n" RESET);
		return (0);
	}
	if (game->ceiling_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid ceiling RGB\n" RESET), 0);
	if (game->floor_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid floor RGB\n" RESET), 0);
	return (1);
}

static int	check_enemy_text(t_enemy *enemies, t_texture *e_txt_s,
		t_texture *e_txt_w1, t_texture *e_txt_w2)
{
	if (enemies == NULL)
		return (1);
	if (!e_txt_s || access(e_txt_s->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: Standing enemy texture not found\n" RESET);
		return (0);
	}
	if (!e_txt_w1 || access(e_txt_w1->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: Walking 1 enemy texture not found\n" RESET);
		return (0);
	}
	if (!e_txt_w2 || access(e_txt_w2->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: Walking 2 enemy texture not found\n" RESET);
		return (0);
	}
	return (1);
}

int	check_data(t_game *game)
{
	if (!game->txt_no || !game->txt_so || !game->txt_we || !game->txt_ea)
		return (ft_fprintf(2, RED "Error: Missing textures\n" RESET), -1);
	if (!check_texture_file(game->txt_no, "North"))
		return (-1);
	if (!check_texture_file(game->txt_so, "South"))
		return (-1);
	if (!check_texture_file(game->txt_we, "West"))
		return (-1);
	if (!check_texture_file(game->txt_ea, "East"))
		return (-1);
	if (!check_enemy_text(game->enemies, game->e_txt_s, game->e_txt_w1,
			game->e_txt_w2))
		return (-1);
	if (!check_texture_file(game->txt_door, "Door"))
		return (-1);
	if (!game->txt_exit && has_exit(game->map.grid))
		return (ft_fprintf(2, RED "Error: Missing exit texture\n" RESET), -1);
	if (game->txt_exit && !check_texture_file(game->txt_exit, "Exit"))
		return (-1);
	if (!check_sprites(game))
		return (-1);
	if (!check_colors(game))
		return (-1);
	return (0);
}
