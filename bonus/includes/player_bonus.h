/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== MOVEMENT CONSTANTS ========== */
# define MOVE_SPEED			0.03
# define ROT_SPEED			0.008
# define MOUSE_SENSITIVITY	0.003
# ifndef SPRINT_MULTIPLIER
#  define SPRINT_MULTIPLIER	1.8
# endif

/* ========== COLLISION CONSTANT ========== */
# define PLAYER_HITBOX	0.25

/* ========== KEY MAPPING - MACOS ========== */
# define KEY_W_M		13
# define KEY_A_M		2
# define KEY_S_M		1
# define KEY_D_M		0
# define KEY_LEFT_M		124
# define KEY_RIGHT_M	123
# define KEY_UP_M		126
# define KEY_DOWN_M		125
# define KEY_ESC_M		53
# define KEY_E_M		14
# define KEY_CTRL_M		256
# define KEY_SHIFT_M	257

/* ========== KEY MAPPING - LINUX ========== */
# define KEY_W_L		119
# define KEY_A_L		97
# define KEY_S_L		115
# define KEY_D_L		100
# define KEY_LEFT_L		65361
# define KEY_RIGHT_L	65363
# define KEY_UP_L		65362
# define KEY_DOWN_L		65364
# define KEY_ESC_L		65307
# define KEY_E_L		101
# define KEY_CTRL_L		65507
# define KEY_SHIFT_L	65505

/* ========== PLAYER FUNCTIONS ========== */
int		is_player_char(char c);
int		get_player_position(t_game *game);

/* ========== MOVEMENT FUNCTIONS ========== */
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	rotate_player(t_game *game, double angle);
int		handle_mouse_press(int button, int x, int y, t_game *game);
int		handle_mouse_move(int x, int y, t_game *game);
int		is_valid_position(t_game *game, double x, double y);

/* ========== KEY HANDLING ========== */
void	init_keys(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
void	update_movement(t_game *game);

#endif /* PLAYER_BONUS_H */
