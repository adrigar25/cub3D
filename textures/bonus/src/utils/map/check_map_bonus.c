/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"

/**
 * ENGLISH: Scans the map grid for an exit tile ('A') and returns 1 if
 *          one is found.
 *
 * SPANISH: Escanea la cuadrícula del mapa en busca de una casilla de
 *          salida ('A') y retorna 1 si se encuentra alguna.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 *
 * @return 1 if an exit exists, 0 otherwise. /
 *         1 si existe una salida, 0 en caso contrario.
 */
int	has_exit(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'A')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * ENGLISH: Runs all map-validity checks in order: emptiness, characters,
 *          player count, wall enclosure, and exit presence.
 *
 * SPANISH: Ejecuta todas las comprobaciones de validez del mapa en orden:
 *          vaciado, carácteres, conteo de jugadores, cerramiento de
 *          paredes y presencia de salida.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 0 on success, -1 on any validation failure. /
 *         0 en éxito, -1 en cualquier fallo de validación.
 */
int	check_map(t_game *game)
{
	char	**map;

	if (game)
		map = game->map.grid;
	else
		map = NULL;
	if (!map || !map[0] || !map[0][0])
		return (ft_fprintf(2, RED "Error: Map is empty\n" RESET), -1);
	if (check_empty_rows(map) == -1)
		return (-1);
	if (check_empty_columns(map) == -1)
		return (-1);
	if (check_valid_characters(game) == -1)
		return (-1);
	if (check_player(map) == -1)
		return (-1);
	if (check_walls(map) == -1)
		return (-1);
	if (!has_exit(map))
		return (ft_fprintf(2, RED "Error: Map has no exit (A)\n" RESET), -1);
	return (0);
}
