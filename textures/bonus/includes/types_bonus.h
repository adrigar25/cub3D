/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

/*
** This header contains ONLY struct definitions — no includes, no prototypes.
** It is the single source of truth for all sub-types used in t_game.
*/

/* ========== KEY STATES ========== */
typedef struct s_keys
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
	int					up;
	int					down;
	int					shift;
}						t_keys;

/* ========== ENEMY ========== */
typedef struct s_enemy
{
	float				x;
	float				y;
	int					tile_x;
	int					tile_y;
	float				last_x;
	float				last_y;
	int					moving;
	int					anim_frame;
	int					anim_timer;
	struct s_enemy		*next;
}						t_enemy;

/* ========== IMAGE ========== */
typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_img;

/* ========== PLAYER ========== */
typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				vertical_dir_x;
	double				vertical_dir_y;
	double				plane_x;
	double				plane_y;
	int					pitch;
}						t_player;

/* ========== TEXTURE (linked list node) ========== */
typedef struct s_texture
{
	char				*name;
	char				*path;
	t_img				img;
	struct s_texture	*next;
}						t_texture;

/* ========== SPRITE INFO ========== */
typedef struct s_sprite_info
{
	double				x;
	double				y;
	double				depth;
	t_img				*tex;
}						t_sprite_info;

/* ========== RAYCAST STATE ========== */
typedef struct s_raycast
{
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					side;
	int					hit;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	int					tex_x;
	double				step;
	double				tex_pos;
}						t_raycast;

/* ========== MINIMAP COORD ========== */
typedef struct s_fcoord
{
	double				x;
	double				y;
}						t_fcoord;

/* ========== HUD ========== */
typedef struct s_hud_rect
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
}						t_hud_rect;

typedef struct s_hud
{
	const char			*title;
	const char			*sub;
	const char			*sub2;
	int					color;
}						t_hud;

#endif /* TYPES_BONUS_H */
