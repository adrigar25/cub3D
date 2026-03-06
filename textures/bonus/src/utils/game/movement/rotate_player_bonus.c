/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "player_bonus.h"
#include <math.h>

/**
 * ENGLISH: Applies a rotation to the player direction and camera plane
 *          vectors using a 2D rotation matrix.
 *
 * SPANISH: Aplica una rotación a los vectores de dirección del jugador y
 *          plano de cámara usando una matriz de rotación 2D.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param angle Rotation angle in radians (positive=left, negative=right). /
 *              Ángulo de rotación en radianes (positivo=izq, negativo=der).
 */
void	apply_rotation(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_val;
	double	sin_val;

	cos_val = cos(angle);
	sin_val = sin(angle);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_val - game->player.dir_y
		* sin_val;
	game->player.dir_y = old_dir_x * sin_val + game->player.dir_y * cos_val;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_val - game->player.plane_y
		* sin_val;
	game->player.plane_y = old_plane_x * sin_val + game->player.plane_y
		* cos_val;
}

/**
 * ENGLISH: Rotates the player view to the left by ROT_SPEED radians.
 *
 * SPANISH: Rota la vista del jugador hacia la izquierda en ROT_SPEED rad.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	rotate_left(t_game *game)
{
	apply_rotation(game, ROT_SPEED);
}

/**
 * ENGLISH: Rotates the player view to the right by ROT_SPEED radians.
 *
 * SPANISH: Rota la vista del jugador hacia la derecha en ROT_SPEED rad.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	rotate_right(t_game *game)
{
	apply_rotation(game, -ROT_SPEED);
}

/**
 * ENGLISH: Rotates the player by the given angle in radians.
 *
 * SPANISH: Rota al jugador el ángulo indicado en radianes.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param angle Rotation angle in radians. / Ángulo de rotación en radianes.
 */
void	rotate_player(t_game *game, double angle)
{
	apply_rotation(game, angle);
}
