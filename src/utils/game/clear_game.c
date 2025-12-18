/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 18:50:15 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	free_map(game->map);
	free(game->textures.color_floor);
	free(game->textures.color_ceiling);
	free(game);
}
