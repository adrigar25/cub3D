/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 18:50:04 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_data_structs(t_game *game)
{
	game->textures.color_floor = malloc(3 * sizeof(int));
	game->textures.color_ceiling = malloc(3 * sizeof(int));
	if (!game->textures.color_floor || !game->textures.color_ceiling)
	{
		free(game->textures.color_floor);
		free(game->textures.color_ceiling);
		return (-1);
	}
	game->textures.color_floor[0] = -1;
	game->textures.color_floor[1] = -1;
	game->textures.color_floor[2] = -1;
	game->textures.color_ceiling[0] = -1;
	game->textures.color_ceiling[1] = -1;
	game->textures.color_ceiling[2] = -1;
	game->map = NULL;
	return (0);
}
