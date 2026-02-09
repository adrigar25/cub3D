/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:47:14 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 12:45:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include "math_utils.h"

int	is_out_of_bounds(int map_x, int map_y, char **map)
{
	if (map_y < 0 || map_x < 0)
		return (1);
	if (!map[map_y] || !map[map_y][map_x])
		return (1);
	return (0);
}

double	calc_wall_impact(t_player player, t_raycast ray)
{
	if (ray.side == 0)
		return (player.pos_y + ray.perp_wall_dist * ray.ray_dir_y);
	else
		return (player.pos_x + ray.perp_wall_dist * ray.ray_dir_x);
}

double	calc_texture_x_coord(double wall_x, int side, double ray_dir,
		int tex_width)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex_width);
	if (side == 0 && ray_dir > 0)
		tex_x = tex_width - tex_x - 1;
	if (side == 1 && ray_dir < 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
