/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:29:01 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 16:31:02 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_ray(t_game *game, int x)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;

	ray->ray_dir_x = game->player.dir_x
		+ game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y
		+ game->player.plane_y * ray->camera_x;

	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
}
