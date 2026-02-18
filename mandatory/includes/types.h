/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:13:56 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
** This header contains ONLY struct definitions — no includes, no prototypes.
** It is the single source of truth for all sub-types used in t_game.
** Include this header anywhere a struct body (not just a pointer) is needed.
*/

/* ========== MAP DATA STRUCTURE ========== */
typedef struct s_map_data
{
	char	**grid;
	int		width;
	int		height;
}			t_map_data;
/* ========== KEY STATES ========== */
typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		up;
	int		down;
}			t_keys;

/* ========== PLAYER ========== */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	vertical_dir_x;
	double	vertical_dir_y;
	double	plane_x;
	double	plane_y;
	int		pitch;
}			t_player;

/* ========== IMAGE ========== */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

/* ========== TEXTURES ========== */
typedef struct s_textures
{
	t_img	no;
	char	*path_no;
	t_img	so;
	char	*path_so;
	t_img	ea;
	char	*path_ea;
	t_img	we;
	char	*path_we;
	int		color_c;
	int		color_f;
}			t_textures;

/* ========== RAYCAST STATE ========== */
typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}			t_raycast;

#endif /* TYPES_H */
