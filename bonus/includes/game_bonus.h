/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

/*
** game_bonus.h no incluye los headers funcionales directamente.
** Las definiciones de structs vienen de types_bonus.h y map_bonus.h.
*/
# include "types_bonus.h"
# include "map_bonus.h"

/* ========== GAME STRUCTURE ========== */
typedef struct s_game
{
	t_map_data			map;
	double				*zbuffer;
	int					mouse_captured;
	int					finished;
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				minimap;
	t_img				img;
	t_texture			*txt_no;
	t_texture			*txt_so;
	t_texture			*txt_ea;
	t_texture			*txt_we;
	t_texture			*txt_door;
	t_texture			*txt_exit;
	t_texture			*e_txt_s;
	t_texture			*e_txt_w1;
	t_texture			*e_txt_w2;
	t_texture			*sprites;
	int					floor_color;
	int					ceiling_color;
	t_raycast			raycast;
	t_keys				keys;
	char				allowed_chars[128];
	int					allowed_count;
	t_enemy				*enemies;
	t_player			player;
	int					score;
}						t_game;

/* ========== GAME LOOP ========== */
void	start_game_loop(t_game *game);

/* ========== CLEANUP ========== */
void	clear_game(t_game *game, int exit_code);

/* ========== GAME EVENTS ========== */
void	check_exit_collision(t_game *game);
void	check_collectibles(t_game *game);
void	draw_score(t_game *game);

/* ========== DOOR ========== */
void	open_door(t_game *game);

#endif /* GAME_BONUS_H */
