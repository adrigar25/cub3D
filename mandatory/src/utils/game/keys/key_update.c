/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "player.h"

/**
 * ENGLISH: Reads the current key states and applies the corresponding
 * 			player movements and rotations.
 *
 * SPANISH: Lee los estados actuales de las teclas y aplica los movimientos
 * 			y rotaciones correspondientes del jugador.
 *
 * @param game Pointer to the game structure. / Puntero al juego.
 */
void	update_movement(t_game *game)
{
	if (game->keys.w || game->keys.up)
		move_forward(game);
	if (game->keys.s || game->keys.down)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
}
