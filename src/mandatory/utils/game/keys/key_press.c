/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/29 23:53:58 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/**
 * ENGLISH: Handle key press events - set key state to 1.
 *
 * SPANISH: Maneja eventos de teclas presionadas
	- establece el estado de la tecla a 1.
 */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC_M)
		exit(0);
	else if (keycode == KEY_W_M)
		game->keys.w = 1;
	else if (keycode == KEY_A_M)
		game->keys.a = 1;
	else if (keycode == KEY_S_M)
		game->keys.s = 1;
	else if (keycode == KEY_D_M)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT_M)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT_M)
		game->keys.right = 1;
	else if (keycode == KEY_UP_M)
		game->keys.up = 1;
	else if (keycode == KEY_DOWN_M)
		game->keys.down = 1;
	return (0);
}
