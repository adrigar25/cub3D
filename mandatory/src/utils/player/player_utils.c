/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:25:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "player.h"

/**
 * ENGLISH: Checks if a character represents a player start position.
 *
 * SPANISH: Comprueba si un carácter representa una posición inicial del jugador.
 *
 * @param c The character to check. / El carácter a comprobar.
 *
 * @return 1 if c is a player char (N/S/E/W), 0 otherwise. /
 * 		1 si c es un carácter de jugador, 0 en caso contrario.
 */
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * ENGLISH: Sets the player direction and camera plane for North/South.
 *
 * SPANISH: Establece la dirección del jugador y el plano de cámara
 * 			para Norte/Sur.
 *
 * @param player Pointer to the player structure. / Puntero al jugador.
 * @param orientation The orientation character ('N' or 'S'). /
 * 		El carácter de orientación ('N' o 'S').
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
 * ENGLISH: Sets the player direction and camera plane for East/West.
 *
 * SPANISH: Establece la dirección del jugador y el plano de cámara
 * 			para Este/Oeste.
 *
 * @param player Pointer to the player structure. / Puntero al jugador.
 * @param orientation The orientation character ('E' or 'W'). /
 * 		El carácter de orientación ('E' o 'W').
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
 * ENGLISH: Sets the player direction and camera plane based on orientation.
 *
 * SPANISH: Establece la dirección del jugador y el plano de cámara según
 * 			la orientación.
 *
 * @param player Pointer to the player structure. / Puntero al jugador.
 * @param orientation The orientation character (N/S/E/W). /
 * 		El carácter de orientación (N/S/E/W).
 */
static void	set_player_direction(t_player *player, char orientation)
{
	if (orientation == 'N' || orientation == 'S')
		set_north_south(player, orientation);
	else
		set_east_west(player, orientation);
}

/**
 * ENGLISH: Scans the map to find the player position and sets direction.
 *
 * SPANISH: Recorre el mapa para encontrar la posición del jugador y
 * 			establece su dirección.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 *
 * @return 0 when the player position is found. /
 * 		0 cuando se encuentra la posición del jugador.
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
				return (0);
			}
		}
	}
	return (0);
}
