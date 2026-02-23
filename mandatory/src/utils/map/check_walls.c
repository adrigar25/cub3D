/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include "player.h"

/**
 * ENGLISH: Fills dx and dy with the direction vector for neighbor index i.
 * 			Covers 8 directions (cardinal + diagonal).
 *
 * SPANISH: Rellena dx y dy con el vector de dirección para el vecino i.
 * 			Cubre 8 direcciones (cardinales + diagonales).
 *
 * @param i Index of the direction (0-7). / Índice de la dirección (0-7).
 * @param dx Pointer to the x component. / Puntero al componente x.
 * @param dy Pointer to the y component. / Puntero al componente y.
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
 * ENGLISH: Checks if the neighbor of cell (x, y) in direction i is a valid
 * 			non-empty map cell.
 *
 * SPANISH: Comprueba si el vecino de la celda (x, y) en dirección i es una
 * 			celda del mapa válida y no vacía.
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 * @param x Row index of the cell. / Índice de fila de la celda.
 * @param y Column index of the cell. / Índice de columna de la celda.
 * @param i Direction index (0-7). / Índice de dirección (0-7).
 *
 * @return 1 if the neighbor is valid, 0 if it is out of bounds or empty. /
 * 		1 si el vecino es válido, 0 si está fuera del mapa o vacío.
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
 * ENGLISH: Verifies that every open cell ('0' or player) in the map is
 * 			surrounded by valid cells in all 8 directions.
 *
 * SPANISH: Verifica que cada celda abierta ('0' o jugador) del mapa esté
 * 			rodeada por celdas válidas en las 8 direcciones.
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 0 if the map is closed, or -1 if a breach is found. /
 * 		0 si el mapa está cerrado, o -1 si se encuentra una brecha.
 */
int	check_walls(char **map)
{
	int	i;
	int	x;
	int	y;

	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (!(map[x][y] == '0' || is_player_char(map[x][y])))
				continue ;
			i = 0;
			while (i < 8)
				if (!is_valid_neighbor(map, x, y, i++))
					return (-1);
		}
	}
	return (0);
}
