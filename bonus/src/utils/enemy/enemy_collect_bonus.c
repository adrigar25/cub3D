/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collect_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:20 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 20:21:12 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include <stdlib.h>

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
