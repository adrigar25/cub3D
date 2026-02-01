
#ifndef MATH_UTILS_H
# define MATH_UTILS_H

// double	dist(double x1, double y1, double x2, double y2);
# include <math.h>

// Vector
void	rotate_vector(double *x, double *y, double angle);

// Geometry
double	fract(double x);

// Camera
double	camera_x(int x, int win_w);

// Map
int		is_out_of_bounds(int map_x, int map_y, char **map);
double	calc_wall_impact(double player_pos, double perp_dist, double ray_dir);
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
