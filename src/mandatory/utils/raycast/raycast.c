/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:05:09 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/24 13:15:51 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, x);
		dda(game);
		draw_column(game, x);
		x++;
	}
	
	// Render remote players after drawing walls
	if (game->network.running)
		render_remote_players(game);
}
