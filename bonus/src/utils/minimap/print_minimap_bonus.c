/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:01:25 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 21:11:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "minimap_bonus.h"
#include "mlx.h"
#include "render_bonus.h"
#include <math.h>

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

static void	blit_pixel(t_game *game, int px, int py, int off[2])
{
	char	*src;
	char	*dst;

	src = game->minimap.addr + (py * game->minimap.line_len + px
			* (game->minimap.bpp / 8));
	dst = game->img.addr + ((off[1] + py) * game->img.line_len + (off[0] + px)
			* (game->img.bpp / 8));
	*(unsigned int *)dst = *(unsigned int *)src;
}

static void	blit_minimap(t_game *game, int off_x, int off_y)
{
	int		px;
	int		py;
	double	cx;
	double	dist;
	int		off[2];

	cx = game->minimap.width / 2.0;
	off[0] = off_x;
	off[1] = off_y;
	py = 0;
	while (py < game->minimap.height)
	{
		px = 0;
		while (px < game->minimap.width)
		{
			dist = sqrt((px - cx) * (px - cx) + (py - cx) * (py - cx));
			if (dist <= cx)
				blit_pixel(game, px, py, off);
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
	blit_minimap(game, minimap_x, minimap_y);
	return (0);
}
