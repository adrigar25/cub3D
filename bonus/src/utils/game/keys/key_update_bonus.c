/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update_bonus.c                                 :+:      :+:    :+:   */
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
 * ENGLISH: Updates player movement each frame based on current key states.
 *
 * SPANISH: Actualiza el movimiento del jugador cada frame según los
 *          estados actuales de las teclas.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	update_movement(t_game *game)
{
	if (game->finished)
		return ;
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
