/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:08:58 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/20 10:27:26 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
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

static int	check_texture_file(char *path, char *label)
{
	if (!path || access(path, F_OK) == -1)
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
		return (1);
	}
	if (game->ceiling_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid ceiling RGB\n" RESET), 1);
	if (game->floor_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid floor RGB\n" RESET), 1);
	return (0);
}

int	check_data(t_game *game)
{
	if (!game->txt_no || !game->txt_so || !game->txt_we || !game->txt_ea)
		return (ft_fprintf(2, RED "Error: faltan texturas\n" RESET), -1);
	if (!check_texture_file(game->txt_no->path, "North"))
		return (-1);
	if (!check_texture_file(game->txt_so->path, "South"))
		return (-1);
	if (!check_texture_file(game->txt_we->path, "West"))
		return (-1);
	if (!check_texture_file(game->txt_ea->path, "East"))
		return (-1);
	if (game->txt_door && !check_texture_file(game->txt_door->path, "Door"))
		return (-1);
	if (game->txt_exit && !check_texture_file(game->txt_exit->path, "Exit"))
		return (-1);
	if (!check_sprites(game))
		return (-1);
	if (!check_colors(game))
		return (-1);
	return (0);
}
