/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 15:05:09 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_data_structs(t_game *game)
{
	game->color_floor = malloc(3 * sizeof(int));
	game->color_ceiling = malloc(3 * sizeof(int));
	if (!game->color_floor || !game->color_ceiling)
	{
		free(game->color_floor);
		free(game->color_ceiling);
		return (-1);
	}
	game->texture_north = NULL;
	game->texture_south = NULL;
	game->texture_west = NULL;
	game->texture_east = NULL;
	game->color_floor[0] = -1;
	game->color_floor[1] = -1;
	game->color_floor[2] = -1;
	game->color_ceiling[0] = -1;
	game->color_ceiling[1] = -1;
	game->color_ceiling[2] = -1;
	game->map = NULL;
	return (0);
}

