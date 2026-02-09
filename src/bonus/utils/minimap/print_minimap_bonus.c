/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:01:25 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/07 19:13:47 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static int	has_floor_nearby(t_game *game, int x, int y)
{
	int	dx;
	int	dy;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (y + dy >= 0 && y + dy < game->map_h && x + dx >= 0
				&& game->map[y + dy] && x + dx < (int)ft_strlen(game->map[y
					+ dy]) && game->map[y + dy][x + dx] == '0')
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

static void	clear_map(t_game *game)
{
	int		x;
	int		y;
	double	cx;
	double	cy;
	double	dist;

	cx = game->minimap.width / 2.0;
	cy = game->minimap.height / 2.0;
	y = -1;
	while (++y < game->minimap.height)
	{
		x = -1;
		while (++x < game->minimap.width)
		{
			dist = sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
			if (dist > cx)
				img_pixel_put(&game->minimap, x, y, 0xFF000000);
			else if (dist > cx - MINIMAP_BORDER)
				img_pixel_put(&game->minimap, x, y, 0x00000000);
			else
				img_pixel_put(&game->minimap, x, y, MINIMAP_WALL_COLOR);
		}
	}
}

static void	put_minimap_tile(t_game *game, int px, int py, double world_x)
{
	int	map_x;
	int	map_y;

	map_x = (int)world_x;
	map_y = (int)game->player.pos_y;
	if (map_y >= 0 && map_y < game->map_h && map_x >= 0 && game->map[map_y]
		&& map_x < (int)ft_strlen(game->map[map_y]))
	{
		if (game->map[map_y][map_x] == '1' && has_floor_nearby(game, map_x,
				map_y))
			img_pixel_put(&game->minimap, px, py, MINIMAP_WALL_COLOR);
		else if (game->map[map_y][map_x] == 'D')
			img_pixel_put(&game->minimap, px, py, MINIMAP_DOOR_COLOR);
		else
			img_pixel_put(&game->minimap, px, py, MINIMAP_FLOOR_COLOR);
	}
}

static void	draw_minimap_point(t_game *game, int px, int py)
{
	double	cx;
	double	cy;
	double	rel_x;
	double	rel_y;
	double	dist;
	double	world_x;

	cx = game->minimap.width / 2.0;
	cy = game->minimap.height / 2.0;
	rel_x = px - cx;
	rel_y = py - cy;
	dist = sqrt(rel_x * rel_x + rel_y * rel_y);
	if (dist <= cx - MINIMAP_BORDER)
	{
		world_x = (-rel_y * game->player.dir_x - rel_x * game->player.dir_y)
			/ (MINIMAP_SCALE / 2) + game->player.pos_x;
		put_minimap_tile(game, px, py, world_x);
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
	clear_map(game);
	draw_rotated_minimap(game);
	draw_player(game, game->minimap.width / 2.0, game->minimap.height / 2.0);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->minimap.img,
		MINIMAP_X, MINIMAP_Y);
	return (0);
}
