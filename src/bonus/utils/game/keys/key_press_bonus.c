/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d_bonus.h"

/**
 * ENGLISH: Handle key press events - set key state to 1.
 *
 * SPANISH: Maneja eventos de teclas presionadas
	- establece el estado de la tecla a 1.
 */
int	handle_keypress(int keycode, t_game *game)
{
	// Handle menu input
	if (game->menu.state == MENU_MAIN)
	{
		handle_menu_key(keycode, game);
		return (0);
	}
	else if (game->menu.state == MENU_MULTIPLAYER)
	{
		handle_multiplayer_menu_key(keycode, game);
		return (0);
	}
	else if (game->menu.state == MENU_MAP_SELECTION)
	{
		handle_map_selection_key(keycode, game);
		return (0);
	}
	else if (game->menu.state == MENU_ENTER_IP)
	{
		handle_enter_ip_key(keycode, game);
		return (0);
	}

	// Handle game input
	if (game->menu.state == GAME_RUNNING)
	{
		if (keycode == KEY_ESC_M)
		{
			// Only server or single player can close the game
			if (!game->network || game->network->is_server)
				exit(0);
			// Clients do nothing on ESC (or could return to menu later)
		}
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
		else if (keycode == KEY_E_M)
			open_door(game);
	}
	return (0);
}
