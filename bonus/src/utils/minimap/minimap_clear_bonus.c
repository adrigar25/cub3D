/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_clear_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "game_bonus.h"
#include "render_bonus.h"
#include "minimap_bonus.h"

static void	clear_pixel(t_game *game, int x, int y, double *c)
{
	double	dist;

	dist = sqrt((x - c[0]) * (x - c[0]) + (y - c[1]) * (y - c[1]));
	if (dist > c[0])
		img_pixel_put(&game->minimap, x, y, 0xFF000000);
	else if (dist > c[0] - MINIMAP_BORDER)
		img_pixel_put(&game->minimap, x, y, MINIMAP_BORDER_COLOR);
	else
		img_pixel_put(&game->minimap, x, y, MINIMAP_WALL_COLOR);
}

void	clear_map(t_game *game)
{
	int		x;
	int		y;
	double	c[2];

	c[0] = game->minimap.width / 2.0;
	c[1] = game->minimap.height / 2.0;
	y = -1;
	while (++y < game->minimap.height)
	{
		x = -1;
		while (++x < game->minimap.width)
			clear_pixel(game, x, y, c);
	}
}
