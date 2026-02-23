/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"

/**
 * ENGLISH: Returns the maximum non-whitespace column index across all rows.
 *
 * SPANISH: Devuelve el índice de columna máximo no-espaciado en todas las
 * 			filas.
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return The length of the longest meaningful row. /
 * 		La longitud de la fila significativa más larga.
 */
static int	get_max_len(char **map)
{
	int	max_len;
	int	i;
	int	current_len;
	int	j;

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
 * ENGLISH: Returns the column index of the first wall ('1') in the first row.
 *
 * SPANISH: Devuelve el índice de columna de la primera pared ('1') en la
 * 			primera fila.
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 * @param max_len Maximum column length. / Longitud máxima de columna.
 *
 * @return The starting column index. / El índice de columna inicial.
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
 * ENGLISH: Checks that no row in the map consists entirely of whitespace.
 *
 * SPANISH: Comprueba que ninguna fila del mapa esté formada únicamente
 * 			por espacios en blanco.
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 0 if no empty rows exist, or -1 if one is found. /
 * 		0 si no hay filas vacías, o -1 si se encuentra alguna.
 */
int	check_empty_rows(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && ft_strchr(" \t\n", map[i][j]) != NULL)
			j++;
		if (map[i][j] == '\0')
			return (-1);
	}
	return (0);
}

/**
 * ENGLISH: Checks that no column within the map's bounds is entirely empty
 * 			(all whitespace from top to bottom).
 *
 * SPANISH: Comprueba que ninguna columna dentro del mapa esté completamente
 * 			vacía (todo espacios de arriba a abajo).
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 0 if no empty columns exist, or -1 if one is found. /
 * 		0 si no hay columnas vacías, o -1 si se encuentra alguna.
 */
int	check_empty_columns(char **map)
{
	int	i;
	int	j;
	int	max_len;

	max_len = get_max_len(map);
	j = get_starting_column(map, max_len) - 1;
	while (++j < max_len)
	{
		i = -1;
		while (map[++i] && j < (int)ft_strlen(map[i]))
			if (ft_strchr(" \t\n", map[i][j]) == NULL)
				break ;
		if (!map[i])
			return (-1);
	}
	return (0);
}
