/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:14:09 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "types.h"

/* ========== GAME STRUCTURE ========== */
typedef struct s_game
{
	t_map_data	map;
	double		*zbuffer;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_textures	textures;
	t_player	player;
	t_raycast	raycast;
	t_keys		keys;
}				t_game;

/* ========== GAME LOOP ========== */
void			start_game_loop(t_game *game);

/* ========== CLEANUP ========== */
void			clear_game(t_game *game);

#endif /* GAME_H */
