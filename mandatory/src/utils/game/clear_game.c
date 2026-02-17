/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_textures(t_game *game)
{
	if (!game)
		return ;
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_we)
		free(game->textures.path_we);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
	if (game->mlx_ptr && game->textures.no.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.no.img);
	if (game->mlx_ptr && game->textures.so.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.so.img);
	if (game->mlx_ptr && game->textures.we.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.we.img);
	if (game->mlx_ptr && game->textures.ea.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.ea.img);
}

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx_ptr && game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	free_textures(game);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_map(game->map);
	free(game);
}
