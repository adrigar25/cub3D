/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:10:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "raycast.h"
#include "game.h"

/**
 * ENGLISH: Apply rotation to player direction and camera plane.
 *          Uses rotation matrix to rotate both direction and plane vectors.
 *
 * SPANISH: Aplica rotación a la dirección del jugador y plano de cámara.
 *          Usa matriz de rotación para rotar ambos vectores.
 *
 * @param game Pointer to game structure
 * @param angle Rotation angle (positive = left, negative = right)
 */
static void	apply_rotation(t_game *game, double angle)
{
	rotate_vector(&game->player.dir_x, &game->player.dir_y, angle);
	rotate_vector(&game->player.plane_x, &game->player.plane_y, angle);
}

/**
 * ENGLISH: Rotate player view to the left.
 *
 * SPANISH: Rotar la vista del jugador hacia la izquierda.
 */
void	rotate_left(t_game *game)
{
	apply_rotation(game, ROT_SPEED);
}

/**
 * ENGLISH: Rotate player view to the right.
 *
 * SPANISH: Rotar la vista del jugador hacia la derecha.
 */
void	rotate_right(t_game *game)
{
	apply_rotation(game, -ROT_SPEED);
}
