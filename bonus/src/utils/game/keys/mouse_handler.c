/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/29 02:35:55 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	handle_mouse(int x, int y, t_game *game)
{
	int	center_x;
	int	center_y;
	int	delta_x;
	int	delta_y;

	center_x = WIN_W / 2;
	center_y = WIN_H / 2;
	delta_x = x - center_x;
	delta_y = y - center_y;
	if (delta_x != 0)
		rotate_player(game, delta_x * MOUSE_SENSITIVITY);
	if (delta_y != 0)
	{
		game->player.pitch -= delta_y * 2;
		if (game->player.pitch > WIN_H / 2)
			game->player.pitch = WIN_H / 2;
		if (game->player.pitch < -WIN_H / 2)
			game->player.pitch = -WIN_H / 2;
	}
	mlx_mouse_move(game->win_ptr, center_x, center_y);
	return (0);
}
