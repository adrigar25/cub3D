/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:36:33 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/30 00:44:08 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	open_door(t_game *game)
{
	int	next_x;
	int	next_y;

	next_x = (int)(game->player.pos_x + game->player.dir_x);
	next_y = (int)(game->player.pos_y + game->player.dir_y);
	if (next_y >= 0 && next_y < game->map_h && next_x >= 0
		&& next_x < game->map_w && game->map[next_y][next_x] == 'D')
	{
		game->map[next_y][next_x] = '0';
	}
}
