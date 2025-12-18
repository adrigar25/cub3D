/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:03:21 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 15:46:57 by agarcia          ###   ########.fr       */
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
	if (init_textures(game) == -1)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free(game->mlx_ptr);
		return (-1);
	}
	return (0);
}

int	init_textures(t_game *game)
{
	int	width;
	int	height;

	game->no_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->texture_north,
			&width, &height);
	game->so_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->texture_south,
			&width, &height);
	game->we_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->texture_west,
			&width, &height);
	game->ea_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->texture_east,
			&width, &height);
	if (!game->no_ptr || !game->so_ptr || !game->we_ptr || !game->ea_ptr)
		return (ft_error("init_textures",
				(char *[]){"Failed to create textures", NULL}));
	return (0);
}
