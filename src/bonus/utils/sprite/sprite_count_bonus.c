/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_count_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:07:20 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/05 23:49:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sprite_helpers_bonus.h"

static int	is_in_window(double x, double y, const t_sprite_window *w)
{
	return (x >= (double)w->min_x && x <= (double)w->max_x
		&& y >= (double)w->min_y && y <= (double)w->max_y);
}

static int	count_map_sprites(t_game *game, const t_sprite_window *w)
{
	int		count;
	int		y;
	int		x;
	char	tile;

	count = 0;
	y = w->min_y;
	while (y <= w->max_y && game->map[y])
	{
		x = w->min_x;
		while (x <= w->max_x && game->map[y][x])
		{
			tile = game->map[y][x];
			if (!ft_strchr("X01NSEW", tile) && sprite_get_texture(game, tile))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	has_valid_enemy_texture(t_game *game, t_enemy *e)
{
	if (e->moving)
		return (game->e_txt_w1 != NULL || game->e_txt_w2 != NULL);
	return (game->e_txt_s != NULL);
}

static int	count_enemy_sprites(t_game *game, const t_sprite_window *w)
{
	int		count;
	t_enemy	*e;

	count = 0;
	e = game->enemies;
	while (e)
	{
		if (is_in_window(e->x, e->y, w) && has_valid_enemy_texture(game, e))
			count++;
		e = e->next;
	}
	return (count);
}

int	sprite_count_total_in_window(t_game *game, const t_sprite_window *w)
{
	return (count_map_sprites(game, w) + count_enemy_sprites(game, w));
}
