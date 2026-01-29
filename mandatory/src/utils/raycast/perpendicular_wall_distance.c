/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perpendicular_wall_distance.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:48:21 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/20 17:59:34 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	perpendicular_wall_distance(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
}
