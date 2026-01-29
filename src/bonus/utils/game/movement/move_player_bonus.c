/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/24 17:10:03 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d_bonus.h"

/**
 * ENGLISH: Apply movement to player position with collision detection.
 *          Validates new position separately for X and Y axes.
 *
 * SPANISH: Aplica movimiento a la posición del jugador con detección de
 *          colisiones. Valida la nueva posición por separado para ejes X e Y.
 */
static void	apply_movement(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dx;
	new_y = game->player.pos_y + dy;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * ENGLISH: Move player forward in the direction they are facing.
 *
 * SPANISH: Mueve al jugador hacia adelante en la dirección que mira.
 */
void	move_forward(t_game *game)
{
	apply_movement(game, game->player.dir_x * MOVE_SPEED, game->player.dir_y
		* MOVE_SPEED);
}

/**
 * ENGLISH: Move player backward (opposite to facing direction).
 *
 * SPANISH: Mueve al jugador hacia atrás (opuesto a la dirección que mira).
 */
void	move_backward(t_game *game)
{
	apply_movement(game, -game->player.dir_x * MOVE_SPEED, -game->player.dir_y
		* MOVE_SPEED);
}

/**
 * ENGLISH: Strafe left (move perpendicular to facing direction, to the left).
 *
 * SPANISH: Moverse hacia la izquierda (perpendicular a la dirección).
 */
void	move_left(t_game *game)
{
	apply_movement(game, -game->player.dir_y * MOVE_SPEED, game->player.dir_x
		* MOVE_SPEED);
}

/**
 * ENGLISH: Strafe right (move perpendicular to facing direction, to the right).
 *
 * SPANISH: Moverse hacia la derecha (perpendicular a la dirección).
 */
void	move_right(t_game *game)
{
	apply_movement(game, game->player.dir_y * MOVE_SPEED, -game->player.dir_x
		* MOVE_SPEED);
}
