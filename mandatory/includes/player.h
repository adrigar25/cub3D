/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:10:18 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_game	t_game;

/* ========== MOVEMENT CONSTANTS ========== */
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.008
# define MOUSE_SENSITIVITY 0.003

/* ========== COLLISION CONSTANT ========== */
# define PLAYER_HITBOX 0.2

/* ========== PLAYER STRUCTURE ========== */
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

/* ========== KEY STATES STRUCTURE ========== */
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
}						t_keys;

/* ========== KEY MAPPING - MACOS ========== */
# define KEY_W_M 13
# define KEY_A_M 2
# define KEY_S_M 1
# define KEY_D_M 0
# define KEY_LEFT_M 124
# define KEY_RIGHT_M 123
# define KEY_UP_M 126
# define KEY_DOWN_M 125
# define KEY_ESC_M 53
# define KEY_E_M 14

/* ========== KEY MAPPING - LINUX ========== */
# define KEY_W_L 119
# define KEY_A_L 97
# define KEY_S_L 115
# define KEY_D_L 100
# define KEY_LEFT_L 65361
# define KEY_RIGHT_L 65363
# define KEY_UP_L 65362
# define KEY_DOWN_L 65364
# define KEY_ESC_L 65307
# define KEY_E_L 101

/* ========== PLAYER FUNCTIONS ========== */
int						is_player_char(char c);
int						get_player_position(t_game *game);

/* ========== MOVEMENT FUNCTIONS ========== */
void					move_forward(t_game *game);
void					move_backward(t_game *game);
void					move_left(t_game *game);
void					move_right(t_game *game);
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);
void					rotate_player(t_game *game, double angle);
int						is_valid_position(t_game *game, double x, double y);

/* ========== KEY HANDLING ========== */
void					init_keys(t_game *game);
int						handle_keypress(int keycode, t_game *game);
int						handle_keyrelease(int keycode, t_game *game);
void					update_movement(t_game *game);

#endif /* PLAYER_H */
