/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "player_bonus.h"

/**
 * ENGLISH: Handle key release events - sets the corresponding key state to 0.
 *
 * SPANISH: Maneja eventos de teclas liberadas - establece el estado de la
 *          tecla correspondiente a 0.
 *
 * @param keycode X11 keycode of the released key. /
 *                Código X11 de la tecla liberada.
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Always 0. / Siempre 0.
 */
int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W_L)
		game->keys.w = 0;
	else if (keycode == KEY_A_L)
		game->keys.a = 0;
	else if (keycode == KEY_S_L)
		game->keys.s = 0;
	else if (keycode == KEY_D_L)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT_L)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT_L)
		game->keys.right = 0;
	else if (keycode == KEY_UP_L)
		game->keys.up = 0;
	else if (keycode == KEY_DOWN_L)
		game->keys.down = 0;
	else if (keycode == KEY_SHIFT_L)
		game->keys.shift = 0;
	return (0);
}
