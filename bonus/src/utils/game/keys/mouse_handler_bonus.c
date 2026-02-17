/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 22:53:38 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// ...existing code...
int	handle_mouse_press(int button, int x, int y, t_game *game)
{
	if (button != 1 || game->mouse_captured)
		return (0);
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	game->mouse_captured = 1;
	mlx_mouse_hide();
	mlx_mouse_move(game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	int	center_x;
	int	center_y;
	int	delta_x;
	int	delta_y;

	if (!game->mouse_captured || game->finished)
		return (0);
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
