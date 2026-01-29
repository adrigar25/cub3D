/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/28 19:01:37 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d_bonus.h"

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

/**
 * ENGLISH: Rotate player by a specific angle.
 *
 * SPANISH: Rotar jugador por un ángulo específico.
 */
void	rotate_player(t_game *game, double angle)
{
	apply_rotation(game, angle);
}
