/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "game.h"

/**
 * ENGLISH: Handles key release events, setting the corresponding key
 * 			state back to 0.
 *
 * SPANISH: Maneja eventos de teclas liberadas, estableciendo el estado
 * 			correspondiente de vuelta a 0.
 *
 * @param keycode The key code of the released key. / Código de la tecla.
 * @param game Pointer to the game structure. / Puntero al juego.
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
	return (0);
}
