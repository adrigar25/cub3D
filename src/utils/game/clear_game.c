/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/19 13:27:26 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	destroy_texture_images(t_game *game)
{
	if (game->textures.no.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.no.img);
	if (game->textures.so.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.so.img);
	if (game->textures.we.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.we.img);
	if (game->textures.ea.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.ea.img);
}

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx_ptr)
	{
		if (game->img.img)
			mlx_destroy_image(game->mlx_ptr, game->img.img);
		destroy_texture_images(game);
		if (game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	}
	if (game->map)
		free_map(game->map);
	free(game);
}
