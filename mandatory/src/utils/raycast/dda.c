/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:31:46 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:15:44 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math_utils.h"

void	init_step_and_side_dist(t_game *game)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->step_x = calc_step(ray->ray_dir_x);
	ray->side_dist_x = calc_side_dist(game->player.pos_x, ray->map_x,
			ray->ray_dir_x, ray->delta_dist_x);
	ray->step_y = calc_step(ray->ray_dir_y);
	ray->side_dist_y = calc_side_dist(game->player.pos_y, ray->map_y,
			ray->ray_dir_y, ray->delta_dist_y);
}

static void	init_delta_dist(t_raycast *ray)
{
	ray->delta_dist_x = calc_delta_dist(ray->ray_dir_x);
	ray->delta_dist_y = calc_delta_dist(ray->ray_dir_y);
}

static void	perform_dda(t_game *game)
{
	t_raycast	*ray;

	ray = &game->raycast;
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
		if (is_out_of_bounds(ray->map_x, ray->map_y, game->map))
		{
			ray->hit = 1;
			break ;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall_height(t_game *game)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->line_height = (int)safe_div(WIN_H, ray->perp_wall_dist, WIN_H);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	ray->draw_start = clamp(ray->draw_start, 0, WIN_H - 1);
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	ray->draw_end = clamp(ray->draw_end, 0, WIN_H - 1);
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
