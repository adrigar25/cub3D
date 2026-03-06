/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perpendicular_wall_distance.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:48:21 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "raycast.h"

/**
 * ENGLISH: Calculates the perpendicular distance from the player to the
 * 			wall hit by the ray, avoiding fisheye distortion.
 *
 * SPANISH: Calcula la distancia perpendicular del jugador a la pared
 * 			impactada por el rayo, evitando la distorsión ojo de pez.
 *
 * @param ray Pointer to the raycast structure. / Puntero al rayo.
 * @param game Pointer to the game structure. / Puntero al juego.
 */
void	perpendicular_wall_distance(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = safe_div(ray->map_x - game->player.pos_x + (1
					- ray->step_x) / 2.0, ray->ray_dir_x, 1e30);
	else
		ray->perp_wall_dist = safe_div(ray->map_y - game->player.pos_y + (1
					- ray->step_y) / 2.0, ray->ray_dir_y, 1e30);
}
