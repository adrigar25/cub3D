/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 15:07:47 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	free(game->texture_north);
	free(game->texture_south);
	free(game->texture_west);
	free(game->texture_east);
	free(game->color_floor);
	free(game->color_ceiling);
	free_map(game->map);
	free(game);
}
