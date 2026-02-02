/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/24 17:10:35 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d_bonus.h"

/**
 * ENGLISH: Update player movement based on current key states.
 *
 * SPANISH: Actualiza el movimiento del jugador basado en los
	estados actuales de las teclas.
 */
void	update_movement(t_game *game)
{
	// Movement
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
	
	// Jump - apply upward force if on ground
	if (game->keys.space && game->player.height <= NORMAL_HEIGHT)
	{
		game->player.z_velocity = JUMP_FORCE;
	}
	
	// Apply gravity
	game->player.height += game->player.z_velocity;
	game->player.z_velocity -= GRAVITY;
	
	// Crouch - lower height
	if (game->keys.ctrl)
	{
		if (game->player.height > CROUCH_HEIGHT)
			game->player.height -= 0.05;
		if (game->player.height < CROUCH_HEIGHT)
			game->player.height = CROUCH_HEIGHT;
	}
	
	// Return to normal height when not crouching
	if (!game->keys.ctrl && game->player.height < NORMAL_HEIGHT && !game->keys.space)
	{
		game->player.height += 0.05;
		if (game->player.height > NORMAL_HEIGHT)
			game->player.height = NORMAL_HEIGHT;
	}
	
	// Ground collision
	if (game->player.height < NORMAL_HEIGHT && !game->keys.ctrl)
	{
		game->player.height = NORMAL_HEIGHT;
		game->player.z_velocity = 0;
	}
	else if (game->player.height < CROUCH_HEIGHT)
	{
		game->player.height = CROUCH_HEIGHT;
		game->player.z_velocity = 0;
	}
}
