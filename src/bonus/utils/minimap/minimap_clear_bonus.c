/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_clear_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/09 17:21:21 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static void	clear_pixel(t_game *game, int x, int y, double *c)
{
	double	dist;

	dist = sqrt((x - c[0]) * (x - c[0]) + (y - c[1]) * (y - c[1]));
	if (dist > c[0])
		img_pixel_put(&game->minimap, x, y, 0xFF000000);
	else if (dist > c[0] - MINIMAP_BORDER)
		img_pixel_put(&game->minimap, x, y, 0x00000000);
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
