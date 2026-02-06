/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 01:23:33 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_HELPERS_BONUS_H
# define SPRITE_HELPERS_BONUS_H

# include "cub3d_bonus.h"

/* ========== SPRITE WINDOW ========== */
typedef struct s_sprite_window
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
}			t_sprite_window;

/* ========== DRAW SPRITE ========== */
typedef struct s_draw_sprite
{
	double	x;
	double	y;
	double	depth;
	t_img	*tex;
}			t_draw_sprite;

/* ========== WINDOW COMPUTATION ========== */
void		sprite_compute_scan_window(t_game *game, t_sprite_window *w);

/* ========== SPRITE COUNTING ========== */
int			sprite_count_total_in_window(t_game *game,
				const t_sprite_window *w);

/* ========== SPRITE APPENDING ========== */
double		sprite_compute_depth(t_game *game, double sx, double sy);
int			sprite_append_map_sprites(t_game *game, const t_sprite_window *w,
				t_draw_sprite *list, int i);
int			sprite_append_enemy_sprites(t_game *game, const t_sprite_window *w,
				t_draw_sprite *list, int i);

/* ========== TEXTURE LOOKUP ========== */
t_texture	*sprite_get_texture(t_game *game, char c);

#endif /* SPRITE_HELPERS_BONUS_H */
