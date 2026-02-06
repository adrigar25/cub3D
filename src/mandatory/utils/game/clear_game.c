/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/04 17:55:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	t_texture	*current;
	t_texture	*next;

	current = game->textures;
	while (current)
	{
		next = current->next;
		if (current->path)
			free(current->path);
		if (current->name)
			free(current->name);
		if (game->mlx_ptr && current->img.img)
			mlx_destroy_image(game->mlx_ptr, current->img.img);
		free(current);
		current = next;
	}
	game->textures = NULL;
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
	free_texture_paths(game);
	free_map(game->map);
	free(game);
}
