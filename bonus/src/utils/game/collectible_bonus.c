/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

/**
 * ENGLISH: Check if the player is standing on a collectible tile ('C').
 *          If so, remove it from the map and increment the score by 1.
 *
 * SPANISH: Comprueba si el jugador está sobre un tile coleccionable ('C').
 *          Si es así, lo elimina del mapa e incrementa el score en 1.
 */
void	check_collectibles(t_game *game)
{
	int	px;
	int	py;

	if (!game || game->finished)
		return ;
	px = (int)game->player.pos_x;
	py = (int)game->player.pos_y;
	if (py < 0 || py >= game->map.height || !game->map.grid[py])
		return ;
	if (px < 0 || !game->map.grid[py][px])
		return ;
	if (game->map.grid[py][px] == 'C')
	{
		game->map.grid[py][px] = '0';
		game->score++;
	}
}
