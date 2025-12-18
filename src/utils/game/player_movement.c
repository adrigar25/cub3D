/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:00:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 18:40:02 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include <math.h>

/**
 * ENGLISH: Check if a position (x, y) is valid (not a wall).
 *
 * SPANISH: Comprueba si una posición (x, y) es válida (no es una pared).
 */
int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;

	// Comprobar límites del mapa
	if (map_y < 0 || map_x < 0)
		return (0);
	if (!game->map[map_y] || !game->map[map_y][map_x])
		return (0);

	// Comprobar si es una pared
	if (game->map[map_y][map_x] == '1')
		return (0);

	return (1);
}

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

/**
 * ENGLISH: Move player backward (opposite to facing direction).
 *
 * SPANISH: Mueve al jugador hacia atrás (opuesto a la dirección que mira).
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;

	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * ENGLISH: Strafe left (move perpendicular to facing direction, to the left).
 *
 * SPANISH: Moverse hacia la izquierda (perpendicular a la dirección, a la izquierda).
 */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	// El vector perpendicular izquierdo es (-dir_y, dir_x)
	new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;

	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * ENGLISH: Strafe right (move perpendicular to facing direction, to the right).
 *
 * SPANISH: Moverse hacia la derecha (perpendicular a la dirección, a la derecha).
 */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	// El vector perpendicular derecho es (dir_y, -dir_x)
	new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;

	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * ENGLISH: Rotate player view to the left.
 *
 * SPANISH: Rotar la vista del jugador hacia la izquierda.
 */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ game->player.dir_y * cos(ROT_SPEED);

	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED)
		+ game->player.plane_y * cos(ROT_SPEED);
}

/**
 * ENGLISH: Rotate player view to the right.
 *
 * SPANISH: Rotar la vista del jugador hacia la derecha.
 */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.dir_y * cos(-ROT_SPEED);

	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ game->player.plane_y * cos(-ROT_SPEED);
}
