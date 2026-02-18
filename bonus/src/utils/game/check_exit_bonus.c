/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 16:15:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_exit_collision(t_game *game)
{
	int		next_x;
	int		next_y;
	double	dx;
	double	dy;
	double	dist;

	next_x = (int)(game->player.pos_x + game->player.dir_x);
	next_y = (int)(game->player.pos_y + game->player.dir_y);
	if (next_y < 0 || next_y >= game->map_h || next_x < 0
		|| next_x >= game->map_w || !game->map[next_y]
		|| game->map[next_y][next_x] != 'A')
		return ;
	dx = (next_x + 0.5) - game->player.pos_x;
	dy = (next_y + 0.5) - game->player.pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 1.1 && !game->finished)
	{
		game->finished = 1;
		ft_fprintf(1, GREEN "Victory! You found the exit!\n" RESET);
		mlx_mouse_show();
	}
}
