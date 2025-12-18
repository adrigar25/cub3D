/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:03:21 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 17:49:50 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_error("init_mlx", (char *[]){"Failed to initialize MLX",
				NULL}));
	game->win_ptr = mlx_new_window(game->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	if (!game->win_ptr)
	{
		free(game->mlx_ptr);
		return (ft_error("init_mlx", (char *[]){"Failed to create window",
				NULL}));
	}
	if (!init_image_buffer(game))
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free(game->mlx_ptr);
		return (ft_error("init_mlx", (char *[]){"Failed to create image buffer",
				NULL}));
	}
	return (0);
}
