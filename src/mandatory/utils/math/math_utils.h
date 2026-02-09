/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:48:15 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 12:48:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "../../cub3d.h"
# include <math.h>

// Vector
void	rotate_vector(double *x, double *y, double angle);

// Geometry
double	fract(double x);

// Camera
double	camera_x(int x, int win_w);

// Map
int		is_out_of_bounds(int map_x, int map_y, char **map);
double	calc_wall_impact(t_player player, t_raycast ray);
double	calc_texture_x_coord(double wall_x, int side, double ray_dir,
			int tex_width);

// Utils
double	safe_div(double num, double denom, double def);
double	clamp(double val, double min, double max);

// Raycast
double	calc_delta_dist(double ray_dir);
int		calc_step(double ray_dir);
double	calc_side_dist(double pos, int map, double ray_dir, double delta_dist);

#endif
