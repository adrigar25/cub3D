/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:44:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "types.h"

typedef struct s_game	t_game;

/* ========== RAYCASTING FUNCTIONS ========== */
void	raycast(t_game *game);
void	init_ray(t_game *game, int x);
void	dda(t_game *game);
void	init_step_and_side_dist(t_game *game);
void	perpendicular_wall_distance(t_raycast *ray, t_game *game);
void	draw_column(t_game *game, int x);

/* ========== MATH UTILITIES ========== */
void	rotate_vector(double *x, double *y, double angle);
double	fract(double x);
double	camera_x(int x, int win_w);
int		is_out_of_bounds(int map_x, int map_y, char **map);
double	calc_wall_impact(t_player player, t_raycast ray);
double	calc_texture_x_coord(double wall_x, int side, double ray_dir,
			int tex_width);
double	safe_div(double num, double denom, double def);
double	clamp(double val, double min, double max);
double	calc_delta_dist(double ray_dir);
int		calc_step(double ray_dir);
double	calc_side_dist(double pos, int map, double ray_dir, double delta_dist);

#endif /* RAYCAST_H */
