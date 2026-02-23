/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:31:46 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "game.h"
#include "render.h"

/**
 * ENGLISH: Calculates the step direction and initial side distances for
 * 			both axes of the current ray.
 *
 * SPANISH: Calcula la dirección del paso y las distancias laterales
 * 			iniciales para ambos ejes del rayo actual.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 */
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

/**
 * ENGLISH: Computes the delta distances (step cost per grid cell) for
 * 			both ray direction components.
 *
 * SPANISH: Calcula las distancias delta (coste de paso por celda) para
 * 			ambos componentes de dirección del rayo.
 *
 * @param ray Pointer to the raycast structure. / Puntero a la estructura
 * 		del rayo.
 */
static void	init_delta_dist(t_raycast *ray)
{
	ray->delta_dist_x = calc_delta_dist(ray->ray_dir_x);
	ray->delta_dist_y = calc_delta_dist(ray->ray_dir_y);
}

/**
 * ENGLISH: Advances the ray step by step through the grid until it hits
 * 			a wall or goes out of bounds.
 *
 * SPANISH: Avanza el rayo celda a celda a través de la cuadrícula hasta
 * 			que golpea una pared o sale de los límites.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 */
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
		if (is_out_of_bounds(ray->map_x, ray->map_y, game->map.grid))
		{
			ray->hit = 1;
			break ;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * ENGLISH: Computes the height of the wall slice to draw and the vertical
 * 			draw range for the current column.
 *
 * SPANISH: Calcula la altura del segmento de pared a dibujar y el rango
 * 			vertical de dibujado para la columna actual.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 */
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
