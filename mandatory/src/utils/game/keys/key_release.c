/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 16:52:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "game.h"

/**
 * ENGLISH: Handle key release events - set key state to 0.
 *
 * SPANISH: Maneja eventos de teclas liberadas
	- establece el estado de la tecla a 0.
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
