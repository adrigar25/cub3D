/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 17:08:51 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "player.h"
#include <stdlib.h>

/**
 * ENGLISH: Handle key press events - set key state to 1.
 *
 * SPANISH: Maneja eventos de teclas presionadas
		- establece el estado de la tecla a 1.
 */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC_L)
	{
		clear_game(game);
		exit(0);
	}
	else if (keycode == KEY_W_L)
		game->keys.w = 1;
	else if (keycode == KEY_A_L)
		game->keys.a = 1;
	else if (keycode == KEY_S_L)
		game->keys.s = 1;
	else if (keycode == KEY_D_L)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT_L)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT_L)
		game->keys.right = 1;
	else if (keycode == KEY_UP_L)
		game->keys.up = 1;
	else if (keycode == KEY_DOWN_L)
		game->keys.down = 1;
	return (0);
}
