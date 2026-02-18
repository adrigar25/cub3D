/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collect_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:20 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 00:59:01 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	enemy_collect_from_map(t_game *game)
{
	int		y;
	int		x;
	t_enemy	*e;

	if (!game || !game->map)
		return ;
	y = 0;
	while (y < game->map_h && game->map[y])
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == 'X')
			{
				e = create_enemy(x, y);
				if (e)
				{
					enemy_add(game, e);
					game->map[y][x] = '0';
				}
			}
			x++;
		}
		y++;
	}
}
