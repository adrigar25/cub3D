/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/11 18:23:02 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

/**
 * ENGLISH: Move player forward in the direction they are facing.
 *
 * SPANISH: Mueve al jugador hacia adelante en la dirección que mira.
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}
