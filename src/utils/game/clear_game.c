/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 17:59:44 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	free_map(game->map);
	free(game->textures.no_ptr);
	free(game->textures.so_ptr);
	free(game->textures.we_ptr);
	free(game->textures.ea_ptr);
	free(game->textures.color_floor);
	free(game->textures.color_ceiling);
	free(game);
}
