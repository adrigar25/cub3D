/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collect_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:20 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include <stdlib.h>

/**
 * ENGLISH: Scans the map grid for 'X' tiles, creates an enemy at each
 *          position, adds it to the game list, and replaces the tile with '0'.
 *
 * SPANISH: Escanea la cuadrícula del mapa en busca de casillas 'X', crea
 *          un enemigo en cada posición, lo añade a la lista del juego y
 *          reemplaza la casilla por '0'.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	enemy_collect_from_map(t_game *game)
{
	int		y;
	int		x;
	t_enemy	*e;

	if (!game || !game->map.grid)
		return ;
	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'X')
			{
				e = create_enemy(x, y);
				if (e)
				{
					enemy_add(game, e);
					game->map.grid[y][x] = '0';
				}
			}
			x++;
		}
		y++;
	}
}
