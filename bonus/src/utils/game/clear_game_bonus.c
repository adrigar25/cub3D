/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:06:54 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "map_bonus.h"
#include "render_bonus.h"
#include "console_bonus.h"
#include "../../libs/mlx/mlx.h"
#include <stdlib.h>

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
		if (mlx && cur->img.img)
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
	free_texture_list(game->mlx_ptr, game->txt_exit);
	free_texture_list(game->mlx_ptr, game->e_txt_s);
	free_texture_list(game->mlx_ptr, game->e_txt_w1);
	free_texture_list(game->mlx_ptr, game->e_txt_w2);
	free_texture_list(game->mlx_ptr, game->sprites);
	game->txt_no = NULL;
	game->txt_so = NULL;
	game->txt_ea = NULL;
	game->txt_we = NULL;
	game->txt_door = NULL;
	game->txt_exit = NULL;
	game->e_txt_s = NULL;
	game->e_txt_w1 = NULL;
	game->e_txt_w2 = NULL;
	game->sprites = NULL;
}

static void	draw_finish_hud(t_game *game, const char *title, const char *sub,
		int color)
{
	t_hud	msg;

	msg.title = title;
	msg.sub = sub;
	msg.sub2 = "Press ESC to exit";
	msg.color = color;
	draw_hud_message(game, msg);
}

void	clear_game(t_game *game, int exit_code)
{
	if (exit_code == -1)
	{
		ft_fprintf(1, GREEN "Exiting game. Goodbye!\n" RESET);
		if (!game)
			return ;
		if (game->mlx_ptr && game->img.img)
			mlx_destroy_image(game->mlx_ptr, game->img.img);
		free_textures(game);
		if (game->mlx_ptr && game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_map(game->map.grid);
		if (game->zbuffer)
			free(game->zbuffer);
		free(game);
	}
	else if (exit_code == 1)
		draw_finish_hud(game, "VICTORY!", "You reached the exit!", 0x00FF55);
	else if (exit_code == 2)
		draw_finish_hud(game, "GAME OVER", "You died!", 0xFF0000);
}
