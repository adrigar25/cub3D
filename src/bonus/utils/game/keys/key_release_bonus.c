/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/24 12:54:27 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d_bonus.h"

/**
 * ENGLISH: Handle key release events - set key state to 0.
 *
 * SPANISH: Maneja eventos de teclas liberadas
	- establece el estado de la tecla a 0.
 */
int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W_M)
		game->keys.w = 0;
	else if (keycode == KEY_A_M)
		game->keys.a = 0;
	else if (keycode == KEY_S_M)
		game->keys.s = 0;
	else if (keycode == KEY_D_M)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT_M)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT_M)
		game->keys.right = 0;
	else if (keycode == KEY_UP_M)
		game->keys.up = 0;
	else if (keycode == KEY_DOWN_M)
		game->keys.down = 0;
	return (0);
}
