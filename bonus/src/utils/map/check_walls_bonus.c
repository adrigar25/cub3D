/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "console_bonus.h"
#include "map_bonus.h"
#include "player_bonus.h"

/**
 * ENGLISH: Computes the dx/dy step for one of 8 neighbour directions
 *          (orthogonal + diagonal) indexed by i.
 *
 * SPANISH: Calcula el paso dx/dy para una de las 8 direcciones de vecino
 *          (órtogonales + diagonales) indexadas por i.
 *
 * @param i Direction index (0-7). / Índice de dirección (0-7).
 * @param dx Output X step. / Paso X de salida.
 * @param dy Output Y step. / Paso Y de salida.
 */
static void	get_direction(int i, int *dx, int *dy)
{
	if (i == 0 || i == 4 || i == 5)
		*dx = 1;
	if (i == 1 || i == 6 || i == 7)
		*dx = -1;
	if (i == 2 || i == 4 || i == 6)
		*dy = 1;
	else if (i == 3 || i == 5 || i == 7)
		*dy = -1;
}

/**
 * ENGLISH: Checks that the neighbour in direction i from (x, y) exists
 *          and is not a space or out-of-bounds cell.
 *
 * SPANISH: Comprueba que el vecino en la dirección i desde (x, y) exista
 *          y no sea una celda de espacio ni esté fuera de límites.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 * @param x Row index. / Índice de fila.
 * @param y Column index. / Índice de columna.
 * @param i Direction index (0-7). / Índice de dirección (0-7).
 *
 * @return 1 if the neighbour is solid, 0 if it is open or out-of-bounds. /
 *         1 si el vecino es sólido, 0 si está abierto o fuera de límites.
 */
static int	is_valid_neighbor(char **map, int x, int y, int i)
{
	int	new_x;
	int	new_y;
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	get_direction(i, &dx, &dy);
	new_x = x + dx;
	new_y = y + dy;
	if (new_x < 0)
		return (0);
	if (!map[new_x])
		return (0);
	if (new_y < 0)
		return (0);
	if (new_y >= (int)ft_strlen(map[new_x]))
		return (0);
	if (ft_strchr(" \0", map[new_x][new_y]))
		return (0);
	return (1);
}

/**
 * ENGLISH: Verifies that all 8 neighbours of cell (x, y) are valid
 *          (i.e. the cell is fully enclosed).
 *
 * SPANISH: Verifica que los 8 vecinos de la celda (x, y) sean válidos
 *          (es decir, que la celda esté completamente rodeada).
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 * @param x Row index. / Índice de fila.
 * @param y Column index. / Índice de columna.
 *
 * @return 1 if all neighbours are valid, -1 if any is open. /
 *         1 si todos los vecinos son válidos, -1 si alguno está abierto.
 */
int	check_directions(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!is_valid_neighbor(map, x, y, i))
			return (-1);
		i++;
	}
	return (1);
}

/**
 * ENGLISH: Iterates over all walkable cells (floor, player, door, 'C')
 *          and verifies that each is fully enclosed by checking all 8
 *          neighbours.
 *
 * SPANISH: Itera sobre todas las celdas transitables (suelo, jugador,
 *          puerta, 'C') y verifica que cada una esté completamente rodeada
 *          comprobando los 8 vecinos.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 *
 * @return 1 on success, -1 if any open wall is found. /
 *         1 en éxito, -1 si se encuentra alguna pared abierta.
 */
int	check_walls(char **map)
{
	int	x;
	int	y;

	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (!(map[x][y] == '0' || is_player_char(map[x][y])
					|| map[x][y] == 'D' || map[x][y] == 'C'))
				continue ;
			if (check_directions(map, x, y) == -1)
			{
				ft_fprintf(2, RED "Error: Open wall or hole ");
				ft_fprintf(2, "at row %d, col %d\n" RESET, x + 1, y + 1);
				return (-1);
			}
		}
	}
	return (1);
}
