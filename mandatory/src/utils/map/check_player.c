/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:15:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "map.h"
#include "player.h"

/**
 * ENGLISH: Verifies that the map contains exactly one player start position
 * 			(N, S, E or W character).
 *
 * SPANISH: Verifica que el mapa contenga exactamente una posición de inicio
 * 			del jugador (carácter N, S, E o W).
 *
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 0 if exactly one player is found, or -1 otherwise. /
 * 		0 si se encuentra exactamente un jugador, o -1 en caso contrario.
 */
int	check_player(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && player_count <= 1)
			player_count += is_player_char(map[i][j++]);
	}
	if (player_count == 0)
		return (ft_fprintf(2, RED "Error: No player found\n" RESET), -1);
	if (player_count > 1)
		return (ft_fprintf(2, RED "Error: Multiple players found\n" RESET), -1);
	return (0);
}
