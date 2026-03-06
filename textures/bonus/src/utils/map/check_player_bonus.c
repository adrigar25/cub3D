/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:15:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "map_bonus.h"
#include "player_bonus.h"
#include "console_bonus.h"

/**
 * ENGLISH: Verifies that the map contains exactly one player starting
 *          position (N, S, E or W).
 *
 * SPANISH: Verifica que el mapa contenga exactamente una posición de
 *          inicio de jugador (N, S, E o W).
 *
 * @param map NULL-terminated map grid. / Cuadrícula del mapa terminada en NULL.
 *
 * @return 0 if exactly one player is found, -1 otherwise. /
 *         0 si se encuentra exactamente un jugador, -1 en caso contrario.
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
	if (player_count != 1)
	{
		ft_fprintf(2, RED "Error: %d players found. ", player_count);
		ft_fprintf(2, RED "Only one of N, S, E or W is allowed\n" RESET);
		return (-1);
	}
	return (0);
}
