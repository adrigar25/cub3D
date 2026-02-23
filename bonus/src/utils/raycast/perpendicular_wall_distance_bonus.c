/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perpendicular_wall_distance_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:48:21 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "raycast_bonus.h"

/**
 * ENGLISH: Calculates the perpendicular distance from the player to the
 *          wall hit, avoiding fisheye effect by using the perpendicular
 *          projection rather than the Euclidean distance.
 *
 * SPANISH: Calcula la distancia perpendicular desde el jugador hasta la
 *          pared impactada, evitando el efecto ojo de pez usando la
 *          proyección perpendicular en lugar de la distancia euclidiana.
 *
 * @param ray Pointer to the raycast data structure. /
 *            Puntero a la estructura de datos del rayo.
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	perpendicular_wall_distance(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
}
