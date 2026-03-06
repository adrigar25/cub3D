/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"

/**
 * ENGLISH: Checks that every character in the map belongs to the set of
 * 			valid map characters (space, 0, 1, N, S, E, W, newline).
 *
 * SPANISH: Comprueba que cada carácter del mapa pertenece al conjunto de
 * 			carácteres válidos (espacio, 0, 1, N, S, E, W, nueva línea).
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 0 if all characters are valid, or -1 if an invalid one is found. /
 * 		0 si todos los carácteres son válidos, o -1 si hay uno inválido.
 */
int	check_valid_characters(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
			if (ft_strchr(" 01NSEW\n", map[i][j++]) == NULL)
				return (-1);
	}
	return (0);
}
