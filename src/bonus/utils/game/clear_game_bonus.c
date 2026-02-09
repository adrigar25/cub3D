/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:06:54 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 18:20:59 by agarcia          ###   ########.fr       */
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

static void	free_texture_list(void *mlx, t_texture *head)
{
	t_texture	*cur;
	t_texture	*next;

	if (!head)
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
	head = NULL;
}

static void	free_textures(t_game *game)
{
	game->txt_no->next = game->txt_so;
	game->txt_so->next = game->txt_ea;
	game->txt_ea->next = game->txt_we;
	game->txt_we->next = game->txt_door;
	game->txt_door->next = NULL;
	free_texture_list(game->mlx_ptr, game->txt_no);
	free_texture_list(game->mlx_ptr, game->sprites);
}

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx_ptr && game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_textures(game);
	free_map(game->map);
	free(game);
}
