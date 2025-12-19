/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/19 12:37:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_data_structs(t_game *game)
{
	if (!game->textures.color_floor || !game->textures.color_ceiling)
	{
		free(game->textures.color_floor);
		free(game->textures.color_ceiling);
		return (-1);
	}
	game->textures.color_ceiling = 0x000000;
	game->textures.color_floor = 0x000000;
	game->map = NULL;
	return (0);
}
