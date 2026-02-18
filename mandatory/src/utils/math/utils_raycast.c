/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:48:36 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:10:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

double	calc_delta_dist(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	return (fabs(1.0 / ray_dir));
}

int	calc_step(double ray_dir)
{
	if (ray_dir < 0)
		return (-1);
	else
		return (1);
}

double	calc_side_dist(double pos, int map, double ray_dir, double delta_dist)
{
	if (ray_dir < 0)
		return ((pos - map) * delta_dist);
	else
		return ((map + 1.0 - pos) * delta_dist);
}
