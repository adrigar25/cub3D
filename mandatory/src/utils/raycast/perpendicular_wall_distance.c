/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perpendicular_wall_distance.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:48:21 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/18 17:10:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "raycast.h"

void	perpendicular_wall_distance(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = safe_div(ray->map_x - game->player.pos_x + (1
					- ray->step_x) / 2.0, ray->ray_dir_x, 1e30);
	else
		ray->perp_wall_dist = safe_div(ray->map_y - game->player.pos_y + (1
					- ray->step_y) / 2.0, ray->ray_dir_y, 1e30);
}
