/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:06:54 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:17:18 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	free_texture_list(void *mlx, t_texture *head)
{
	t_texture	*cur;
	t_texture	*next;

	if (!mlx || !head)
		return ;
	cur = head;
	while (cur)
	{
		next = cur->next;
		if (cur->path)
			free(cur->path);
		if (cur->name)
			free(cur->name);
		if (cur->img.img)
			mlx_destroy_image(mlx, cur->img.img);
		free(cur);
		cur = next;
	}
}

static void	free_textures(t_game *game)
{
	if (!game)
		return ;
	free_texture_list(game->mlx_ptr, game->txt_no);
	free_texture_list(game->mlx_ptr, game->txt_so);
	free_texture_list(game->mlx_ptr, game->txt_ea);
	free_texture_list(game->mlx_ptr, game->txt_we);
	free_texture_list(game->mlx_ptr, game->txt_door);
	free_texture_list(game->mlx_ptr, game->sprites);
	game->txt_no = NULL;
	game->txt_so = NULL;
	game->txt_ea = NULL;
	game->txt_we = NULL;
	game->txt_door = NULL;
	game->sprites = NULL;
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