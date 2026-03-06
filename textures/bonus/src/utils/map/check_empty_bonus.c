/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_bonus.c                                :+:      :+:    :+:   */
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

/**
 * ENGLISH: Computes the maximum non-whitespace column index across all
 *          map rows.
 *
 * SPANISH: Calcula el índice de columna no-espacio máximo en todas las
 *          filas del mapa.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 *
 * @return Maximum content width, or 0 if map is NULL. /
 *         Ancho de contenido máximo, o 0 si el mapa es NULL.
 */
static int	get_max_len(char **map)
{
	int	max_len;
	int	i;
	int	current_len;
	int	j;

	if (!map)
		return (0);
	max_len = 0;
	i = 0;
	while (map[i])
	{
		current_len = 0;
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(" \t\n", map[i][j]) == NULL)
				current_len = j + 1;
			j++;
		}
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

/**
 * ENGLISH: Finds the first column index that contains a '1' wall tile
 *          in the first row of the map.
 *
 * SPANISH: Encuentra el primer índice de columna que contiene una casilla
 *          de pared '1' en la primera fila del mapa.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 * @param max_len Maximum column width. / Ancho de columna máximo.
 *
 * @return Starting column index. / Índice de columna de inicio.
 */
static int	get_starting_column(char **map, int max_len)
{
	int	start;

	start = 0;
	while (start < max_len && map[0][start] && map[0][start] != '1')
		start++;
	return (start);
}

/**
 * ENGLISH: Checks that no row in the map consists entirely of whitespace
 *          characters.
 *
 * SPANISH: Comprueba que ninguna fila del mapa esté compuesta íntegramente
 *          de caracteres de espacio en blanco.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 *
 * @return 0 if all rows are non-empty, -1 if an empty row is found. /
 *         0 si todas las filas son no vacías, -1 si se encuentra una vacía.
 */
int	check_empty_rows(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && ft_strchr(" \t\n", map[i][j]) != NULL)
			j++;
		if (map[i][j] == '\0')
			return (ft_fprintf(2, RED "Error: Empty row at line %d\n" RESET, i
					+ 1), -1);
		i++;
	}
	return (0);
}

/**
 * ENGLISH: Checks that no column within the content area is entirely
 *          made of whitespace across all map rows.
 *
 * SPANISH: Comprueba que ninguna columna dentro del área de contenido
 *          esté formada íntegramente por espacios en blanco en todas las
 *          filas del mapa.
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 *
 * @return 0 if all columns are valid, -1 if an empty column is found. /
 *         0 si todas las columnas son válidas, -1 si se encuentra una vacía.
 */
int	check_empty_columns(char **map)
{
	int	i;
	int	j;
	int	max_len;

	if (!map)
		return (-1);
	max_len = get_max_len(map);
	j = get_starting_column(map, max_len) - 1;
	while (++j < max_len)
	{
		i = -1;
		while (map[++i] && j < (int)ft_strlen(map[i]))
			if (ft_strchr(" \t\n", map[i][j]) == NULL)
				break ;
		if (!map[i])
			return (ft_fprintf(2, RED "Error: Empty column at col %d\n" RESET, j
					+ 1), -1);
	}
	return (0);
}
