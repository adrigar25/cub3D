/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:31:46 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/30 15:51:24 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	init_step_and_side_dist(t_game *game)
{
	if (game->raycast.ray_dir_x < 0)
	{
		game->raycast.step_x = -1;
		game->raycast.side_dist_x = (game->player.pos_x - game->raycast.map_x)
			* game->raycast.delta_dist_x;
	}
	else
	{
		game->raycast.step_x = 1;
		game->raycast.side_dist_x = (game->raycast.map_x + 1.0
				- game->player.pos_x) * game->raycast.delta_dist_x;
	}
	if (game->raycast.ray_dir_y < 0)
	{
		game->raycast.step_y = -1;
		game->raycast.side_dist_y = (game->player.pos_y - game->raycast.map_y)
			* game->raycast.delta_dist_y;
	}
	else
	{
		game->raycast.step_y = 1;
		game->raycast.side_dist_y = (game->raycast.map_y + 1.0
				- game->player.pos_y) * game->raycast.delta_dist_y;
	}
}

static void	init_delta_dist(t_raycast *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	perform_dda(t_game *game)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1'
			|| game->map[ray->map_y][ray->map_x] == 'D')
			ray->hit = 1;
	}
}

static void	calc_wall_height(t_game *game)
{
	t_raycast	*ray;
	int			height_offset;

	ray = &game->raycast;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	height_offset = (int)(game->player.height * WIN_H) + game->player.pitch;
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2 + height_offset;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2 + height_offset;
}

/**
 * ENGLISH: Perform the Digital Differential Analyzer (DDA) algorithm to find
 * 		the intersection of the ray with a wall in the game map.
 * 		(Collision with walls)
 *
 * SPANISH: Realiza el algoritmo del Analizador Diferencial Digital (DDA) para
 * 		encontrar la intersección del rayo con una pared en el mapa del juego.
 * 		(Colisiones con paredes)
 *
 * @param game Pointer to the game structure containing raycasting data.
 */
void	dda(t_game *game)
{
	game->raycast.hit = 0;
	init_delta_dist(&game->raycast);
	init_step_and_side_dist(game);
	perform_dda(game);
	perpendicular_wall_distance(&game->raycast, game);
	calc_wall_height(game);
}
