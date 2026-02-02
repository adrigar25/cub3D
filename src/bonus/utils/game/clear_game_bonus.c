/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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
	if (game->textures.door.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.door.img);
}

static void	free_texture_paths(t_game *game)
{
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_we)
		free(game->textures.path_we);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
	if (game->textures.path_door)
		free(game->textures.path_door);
	game->textures.path_no = NULL;
	game->textures.path_so = NULL;
	game->textures.path_we = NULL;
	game->textures.path_ea = NULL;
	game->textures.path_door = NULL;
}

void	clear_game_data(t_game *game)
{
	if (!game)
		return;
	destroy_texture_images(game);
	free_texture_paths(game);
	free_map(game->map);
	game->map = NULL;
}

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	if (game->network)
		cleanup_network(game);
	if (game->mlx_ptr && game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	destroy_texture_images(game);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_texture_paths(game);
	free_map(game->map);
	free(game);
}
