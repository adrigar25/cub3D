/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:31:46 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"
#include <math.h>

/**
 * ENGLISH: Initialises the DDA step direction and initial side distances
 *          for x and y based on the ray direction.
 *
 * SPANISH: Inicializa la dirección de paso del DDA y las distancias de
 *          lado iniciales para x e y según la dirección del rayo.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
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

/**
 * ENGLISH: Precomputes the delta distance (distance between consecutive
 *          x/y grid crossings) for both axes of the ray.
 *
 * SPANISH: Precalcula la distancia delta (distancia entre cruces
 *          consecutivos de la cuadrícula x/y) para ambos ejes del rayo.
 *
 * @param ray Pointer to the raycast structure. /
 *            Puntero a la estructura del rayo.
 */
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

/**
 * ENGLISH: Steps the ray through the map grid one cell at a time until
 *          it hits a wall, door or exit tile.
 *
 * SPANISH: Avanza el rayo por la cuadrícula del mapa celda a celda hasta
 *          que impacta con una pared, puerta o casilla de salida.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
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
		if (game->map.grid[ray->map_y][ray->map_x] == '1'
			|| game->map.grid[ray->map_y][ray->map_x] == 'D'
			|| game->map.grid[ray->map_y][ray->map_x] == 'A')
			ray->hit = 1;
	}
}

/**
 * ENGLISH: Computes the wall stripe height and the vertical draw range
 *          from the perpendicular wall distance.
 *
 * SPANISH: Calcula la altura de la franja de pared y el rango de dibujo
 *          vertical a partir de la distancia perpendicular a la pared.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
static void	calc_wall_height(t_game *game)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2 + game->player.pitch;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2 + game->player.pitch;
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
