/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:01:25 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 02:21:46 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_minimap_point(t_game *game, int px, int py)
{
	double		c[2];
	double		rel_x;
	double		rel_y;
	double		dist;
	t_fcoord	world;

	c[0] = game->minimap.width / 2.0;
	c[1] = game->minimap.height / 2.0;
	rel_x = px - c[0];
	rel_y = py - c[1];
	dist = sqrt(rel_x * rel_x + rel_y * rel_y);
	if (dist <= c[0] - MINIMAP_BORDER)
	{
		world.x = (-rel_y * game->player.dir_x - rel_x * game->player.dir_y)
			/ (MINIMAP_SCALE / 2) + game->player.pos_x;
		world.y = (-rel_y * game->player.dir_y + rel_x * game->player.dir_x)
			/ (MINIMAP_SCALE / 2) + game->player.pos_y;
		put_minimap_tile(game, px, py, world);
	}
}

static void	draw_rotated_minimap(t_game *game)
{
	int	px;
	int	py;

	py = 0;
	while (py < game->minimap.height)
	{
		px = 0;
		while (px < game->minimap.width)
		{
			draw_minimap_point(game, px, py);
			px++;
		}
		py++;
	}
}

int	render_minimap(t_game *game)
{
	int	minimap_x;
	int	minimap_y;

	minimap_x = WIN_W - MINIMAP_W - 10;
	minimap_y = WIN_H - MINIMAP_H - 10;
	clear_map(game);
	draw_rotated_minimap(game);
	draw_player(game, game->minimap.width / 2.0, game->minimap.height / 2.0);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->minimap.img,
		minimap_x, minimap_y);
	return (0);
}
