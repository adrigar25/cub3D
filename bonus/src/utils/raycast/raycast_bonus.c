/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:05:09 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"

void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, x);
		dda(game);
		draw_column(game, x);
		game->zbuffer[x] = game->raycast.perp_wall_dist;
		x++;
	}
}
