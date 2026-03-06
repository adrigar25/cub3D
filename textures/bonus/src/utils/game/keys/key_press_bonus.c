/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "player_bonus.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * ENGLISH: Handles the ESC key press: frees resources and exits the game.
 *
 * SPANISH: Maneja la pulsación de la tecla ESC: libera recursos y sale.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Does not return (calls exit). / No retorna (llama a exit).
 */
static int	handle_esc(t_game *game)
{
	clear_game(game, -1);
	exit(0);
}

/**
 * ENGLISH: Handle key press events - sets the corresponding key state to 1.
 *
 * SPANISH: Maneja eventos de teclas presionadas - establece el estado de
 *          la tecla correspondiente a 1.
 *
 * @param keycode X11 keycode of the pressed key. /
 *                Código X11 de la tecla pulsada.
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Always 0. / Siempre 0.
 */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC_L)
		handle_esc(game);
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
	else if (keycode == KEY_SHIFT_L)
		game->keys.shift = 1;
	else if (keycode == KEY_E_L)
		open_door(game);
	else if (keycode == KEY_CTRL_L)
		game->mouse_captured = 0;
	return (0);
}
