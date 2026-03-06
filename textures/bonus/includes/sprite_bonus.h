/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_BONUS_H
# define SPRITE_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== SPRITE PERFORMANCE ========== */
# ifndef SPRITE_SCAN_RADIUS_TILES
#  define SPRITE_SCAN_RADIUS_TILES 8
# endif

/* ========== SPRITE WINDOW ========== */
typedef struct s_sprite_window
{
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
}						t_sprite_window;

/* ========== DRAW SPRITE ========== */
typedef struct s_draw_sprite
{
	double				x;
	double				y;
	double				depth;
	t_img				*tex;
}						t_draw_sprite;

/* ========== SPRITE BOUNDS ========== */
typedef struct s_sprite_bounds
{
	int					draw_start_y;
	int					draw_end_y;
	int					draw_start_x;
	int					draw_start_x_orig;
	int					draw_end_x;
	int					sprite_height;
	int					sprite_width;
	double				y0;
}						t_sprite_bounds;

/* ========== SPRITE DRAW CONTEXT ========== */
typedef struct s_sprite_ctx
{
	t_game				*game;
	t_img				*tex;
	t_sprite_bounds		b;
	double				ty;
}						t_sprite_ctx;

/* ========== WINDOW COMPUTATION ========== */
void					sprite_compute_scan_window(t_game *game,
							t_sprite_window *w);

/* ========== SPRITE COUNTING ========== */
int						sprite_count_total_in_window(t_game *game,
							const t_sprite_window *w);

/* ========== SPRITE APPENDING ========== */
double					sprite_compute_depth(t_player *p, double sx, double sy);
int						sprite_append_map_sprites(t_game *game,
							const t_sprite_window *w, t_draw_sprite *list,
							int i);
int						sprite_append_enemy_sprites(t_game *game,
							const t_sprite_window *w, t_draw_sprite *list,
							int i);

/* ========== SPRITE DRAWING HELPERS ========== */
void					sprite_compute_size(t_img *texture, double transform_y,
							int *height, int *width);
void					sprite_compute_y_bounds(int height, int screen_x,
							int pitch, t_sprite_bounds *b);
void					sprite_compute_x_bounds(int width, int screen_x,
							int *scr_out, t_sprite_bounds *b);
void					sprite_draw_at(t_game *game, t_img *texture,
							double world_x, double world_y);
void					sprite_render(t_game *game);

/* ========== TEXTURE LOOKUP ========== */
t_texture				*sprite_get_texture(t_game *game, char c);

#endif /* SPRITE_BONUS_H */
