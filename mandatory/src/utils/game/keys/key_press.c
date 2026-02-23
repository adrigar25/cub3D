/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "player.h"
#include <stdlib.h>

/**
 * ENGLISH: Handles key press events, setting the corresponding key state
 * 			to 1. ESC key exits the game immediately.
 *
 * SPANISH: Maneja eventos de teclas presionadas, estableciendo el estado
 * 			correspondiente a 1. La tecla ESC cierra el juego.
 *
 * @param keycode The key code of the pressed key. / Código de la tecla.
 * @param game Pointer to the game structure. / Puntero al juego.
 *
 * @return Always 0. / Siempre 0.
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
