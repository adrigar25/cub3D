/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 19:03:07 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static int	check_texture_file(char *path, char *direction)
{
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: %s texture file not found\n" RESET,
			direction);
		return (-1);
	}
	return (0);
}

static int	map_has_doors(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_colors(t_game *game)
{
	if (game->textures.color_f == -1 || game->textures.color_c == -1)
	{
		ft_fprintf(2, RED "Error: Missing floor or ceiling color\n" RESET);
		return (-1);
	}
	if (game->textures.color_c == -2)
		return (ft_fprintf(2, RED "Error: Invalid ceiling RGB\n" RESET), -1);
	if (game->textures.color_f == -2)
		return (ft_fprintf(2, RED "Error: Invalid floor RGB\n" RESET), -1);
	return (0);
}

int	check_data(t_game *game_data)
{
	if (check_texture_file(game_data->textures.path_no, "North") == -1)
		return (-1);
	if (check_texture_file(game_data->textures.path_so, "South") == -1)
		return (-1);
	if (check_texture_file(game_data->textures.path_we, "West") == -1)
		return (-1);
	if (check_texture_file(game_data->textures.path_ea, "East") == -1)
		return (-1);
	// Only check door texture if map has doors
	if (map_has_doors(game_data->map))
	{
		if (check_texture_file(game_data->textures.path_door, "Door") == -1)
			return (-1);
	}
	if (check_colors(game_data) == -1)
		return (-1);
	return (0);
}
