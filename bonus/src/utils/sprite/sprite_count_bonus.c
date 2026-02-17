/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_count_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:07:20 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite_helpers_bonus.h"

static int	spr_is_in_window(double x, double y, const t_sprite_window *w)
{
	return (x >= (double)w->min_x && x <= (double)w->max_x
		&& y >= (double)w->min_y && y <= (double)w->max_y);
}

static int	spr_count_map(t_game *game, const t_sprite_window *w)
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

static int	spr_has_enemy_texture(t_game *game, t_enemy *e)
{
	if (e->moving)
		return (game->e_txt_w1 != NULL || game->e_txt_w2 != NULL);
	return (game->e_txt_s != NULL);
}

static int	spr_count_enemies(t_game *game, const t_sprite_window *w)
{
	int		count;
	t_enemy	*e;

	count = 0;
	e = game->enemies;
	while (e)
	{
		if (spr_is_in_window(e->x, e->y, w) && spr_has_enemy_texture(game, e))
			count++;
		e = e->next;
	}
	return (count);
}

int	sprite_count_total_in_window(t_game *game, const t_sprite_window *w)
{
	return (spr_count_map(game, w) + spr_count_enemies(game, w));
}
