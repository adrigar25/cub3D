/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:36:33 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "player_bonus.h"

/**
 * ENGLISH: Opens a door tile ('D') immediately in front of the player
 *          by replacing it with a floor tile ('0').
 *
 * SPANISH: Abre la casilla de puerta ('D') inmediatamente delante del
 *          jugador reemplazándola por una casilla de suelo ('0').
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	open_door(t_game *game)
{
	int	next_x;
	int	next_y;

	next_x = (int)(game->player.pos_x + game->player.dir_x);
	next_y = (int)(game->player.pos_y + game->player.dir_y);
	if (next_y >= 0 && next_y < game->map.height && next_x >= 0
		&& next_x < game->map.width && game->map.grid[next_y][next_x] == 'D')
	{
		game->map.grid[next_y][next_x] = '0';
	}
}
