/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:01:25 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/05 21:54:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static int	has_floor_nearby(t_game *game, int x, int y)
{
	int	dx;
	int	dy;
	int	check_x;
	int	check_y;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			check_x = x + dx;
			check_y = y + dy;
			if (check_y >= 0 && check_y < game->map_h && check_x >= 0
				&& game->map[check_y]
				&& check_x < (int)ft_strlen(game->map[check_y])
				&& game->map[check_y][check_x] == '0')
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
	double	center_x;
	double	center_y;
	double	distance;

	center_x = game->minimap.width / 2.0;
	center_y = game->minimap.height / 2.0;
	y = -1;
	while (++y < game->minimap.height)
	{
		x = -1;
		while (++x < game->minimap.width)
		{
			distance = sqrt((x - center_x) * (x - center_x) + (y - center_y)
					* (y - center_y));
			if (distance > center_x)
				img_pixel_put(&game->minimap, x, y, 0xFF000000);
			else if (distance > center_x - MINIMAP_BORDER)
				img_pixel_put(&game->minimap, x, y, 0x00000000);
			else
				img_pixel_put(&game->minimap, x, y, MINIMAP_WALL_COLOR);
		}
	}
}

static void	draw_rotated_minimap(t_game *game, double tile_size,
		double center_x, double center_y)
{
	int		px;
	int		py;
	double	rel_x;
	double	rel_y;
	double	world_x;
	double	world_y;
	int		map_x;
	int		map_y;
	double	radius;
	double	distance;

	radius = center_x;
	py = 0;
	while (py < game->minimap.height)
	{
		px = 0;
		while (px < game->minimap.width)
		{
			rel_x = px - center_x;
			rel_y = py - center_y;
			distance = sqrt(rel_x * rel_x + rel_y * rel_y);
			if (distance <= radius - MINIMAP_BORDER)
			{
				world_x = (-rel_y * game->player.dir_x - rel_x
						* game->player.dir_y) / (tile_size / 2)
					+ game->player.pos_x;
				world_y = (-rel_y * game->player.dir_y + rel_x
						* game->player.dir_x) / (tile_size / 2)
					+ game->player.pos_y;
				map_x = (int)world_x;
				map_y = (int)world_y;
				if (map_y >= 0 && map_y < game->map_h && map_x >= 0
					&& game->map[map_y]
					&& map_x < (int)ft_strlen(game->map[map_y]))
				{
					if (game->map[map_y][map_x] == '1' && has_floor_nearby(game,
							map_x, map_y))
						img_pixel_put(&game->minimap, px, py,
							MINIMAP_WALL_COLOR);
					else if (game->map[map_y][map_x] == 'D')
						img_pixel_put(&game->minimap, px, py,
							MINIMAP_DOOR_COLOR);
					else
						img_pixel_put(&game->minimap, px, py,
							MINIMAP_FLOOR_COLOR);
				}
			}
			px++;
		}
		py++;
	}
}

int	render_minimap(t_game *game)
{
	double	tile_size;
	double	center_x;
	double	center_y;
	int		pos_x;
	int		pos_y;

	tile_size = MINIMAP_SCALE;
	center_x = game->minimap.width / 2.0;
	center_y = game->minimap.height / 2.0;
	clear_map(game);
	draw_rotated_minimap(game, tile_size, center_x, center_y);
	draw_player(game, center_x, center_y);
	pos_x = MINIMAP_X;
	pos_y = MINIMAP_Y;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->minimap.img,
		pos_x, pos_y);
	return (0);
}
