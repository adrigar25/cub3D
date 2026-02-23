/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:25:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "player_bonus.h"

/**
 * ENGLISH: Returns 1 if the character represents a valid player starting
 *          direction (N, S, E or W).
 *
 * SPANISH: Retorna 1 si el carácter representa una dirección de inicio
 *          de jugador válida (N, S, E o W).
 *
 * @param c Character to check. / Carácter a comprobar.
 *
 * @return 1 if player char, 0 otherwise. /
 *         1 si es carácter de jugador, 0 en caso contrario.
 */
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * ENGLISH: Sets the initial direction and camera plane for North/South
 *          orientations.
 *
 * SPANISH: Establece la dirección inicial y el plano de cámara para
 *          orientaciones Norte/Sur.
 *
 * @param player Pointer to the player structure. /
 *               Puntero a la estructura del jugador.
 * @param orientation Starting orientation character ('N' or 'S'). /
 *                    Carácter de orientación inicial ('N' o 'S').
 */
static void	set_north_south(t_player *player, char orientation)
{
	player->dir_x = 0;
	player->plane_y = 0;
	if (orientation == 'N')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
}

/**
 * ENGLISH: Sets the initial direction and camera plane for East/West
 *          orientations.
 *
 * SPANISH: Establece la dirección inicial y el plano de cámara para
 *          orientaciones Este/Oeste.
 *
 * @param player Pointer to the player structure. /
 *               Puntero a la estructura del jugador.
 * @param orientation Starting orientation character ('E' or 'W'). /
 *                    Carácter de orientación inicial ('E' o 'W').
 */
static void	set_east_west(t_player *player, char orientation)
{
	player->dir_y = 0;
	player->plane_x = 0;
	if (orientation == 'E')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	else
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
}

/**
 * ENGLISH: Dispatches to the correct axis-specific setter based on the
 *          orientation character.
 *
 * SPANISH: Delega al setter de eje correcto según el carácter de
 *          orientación.
 *
 * @param player Pointer to the player structure. /
 *               Puntero a la estructura del jugador.
 * @param orientation Orientation character (N, S, E or W). /
 *                    Carácter de orientación (N, S, E o W).
 */
static void	set_player_direction(t_player *player, char orientation)
{
	if (orientation == 'N' || orientation == 'S')
		set_north_south(player, orientation);
	else
		set_east_west(player, orientation);
}

/**
 * ENGLISH: Scans the map grid for a player character, sets its floating-
 *          point position and initial direction in the game structure.
 *
 * SPANISH: Escanea la cuadrícula del mapa en busca de un carácter de
 *          jugador, establece su posición de punto flotante y la dirección
 *          inicial en la estructura del juego.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Always 0. / Siempre 0.
 */
int	get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.grid[++i])
	{
		j = -1;
		while (game->map.grid[i][++j])
		{
			if (is_player_char(game->map.grid[i][j]))
			{
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				set_player_direction(&game->player, game->map.grid[i][j]);
			}
		}
	}
	return (0);
}
