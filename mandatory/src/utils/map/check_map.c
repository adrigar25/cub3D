/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "map.h"

/**
 * ENGLISH: Runs all map validation checks: empty rows/columns, valid
 * 			characters, player count and closed walls.
 *
 * SPANISH: Ejecuta todas las validaciones del mapa: filas/columnas vacías,
 * 			carácteres válidos, contador de jugadores y paredes cerradas.
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 0 if the map is valid, or -1 if any check fails. /
 * 		0 si el mapa es válido, o -1 si alguna comprobación falla.
 */
int	check_map(char **map)
{
	if (!map || !map[0] || !map[0][0])
		return (ft_fprintf(2, RED "Error: Map is empty\n" RESET), -1);
	if (check_empty_rows(map) == -1)
		return (ft_fprintf(2, RED "Error: Map has empty lines\n" RESET), -1);
	if (check_empty_columns(map) == -1)
		return (ft_fprintf(2, RED "Error: Map has empty cols\n" RESET), -1);
	if (check_valid_characters(map) == -1)
		return (ft_fprintf(2, RED "Error: Invalid char in map\n" RESET), -1);
	if (check_player(map) == -1)
		return (-1);
	if (check_walls(map) == -1)
		return (ft_fprintf(2, RED "Error: Map not closed\n" RESET), -1);
	return (0);
}
