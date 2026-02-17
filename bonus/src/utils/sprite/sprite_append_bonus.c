/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_append_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:31 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 22:20:45 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite_helpers_bonus.h"

double	sprite_compute_depth(t_player *p, double sx, double sy)
{
	double	x;
	double	y;
	double	inv_det;
	double	transform_y;

	x = sx + 0.5 - p->pos_x;
	y = sy + 0.5 - p->pos_y;
	inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	transform_y = inv_det * (-p->plane_y * x + p->plane_x * y);
	if (transform_y > 0.05)
		return (transform_y);
	return (0.0);
}

static void	add_sprite_info(t_draw_sprite *new, double x, double y,
		double depth)
{
	new->x = x;
	new->y = y;
	new->depth = depth;
}

int	sprite_append_map_sprites(t_game *game, const t_sprite_window *w,
		t_draw_sprite *list, int i)
{
	int			y;
	int			x;
	char		tile;
	double		depth;
	t_texture	*tex;

	y = w->min_y - 1;
	while (y++ <= w->max_y && game->map[y])
	{
		x = w->min_x - 1;
		while (x++ <= w->max_x && game->map[y][x])
		{
			tile = game->map[y][x];
			if (ft_strchr("X01NSEWA", tile))
				continue ;
			tex = sprite_get_texture(game, tile);
			depth = sprite_compute_depth(&game->player, x, y);
			if (tex && tex->img.img && depth > 0.0)
			{
				add_sprite_info(&list[i], x + 0.5, y + 0.5, depth);
				list[i++].tex = &tex->img;
			}
		}
	}
	return (i);
}

static t_texture	*get_enemy_texture(t_game *game, t_enemy *e)
{
	if (e->moving)
	{
		if (e->anim_frame == 0)
			return (game->e_txt_w1);
		return (game->e_txt_w2);
	}
	return (game->e_txt_s);
}

int	sprite_append_enemy_sprites(t_game *game, const t_sprite_window *w,
		t_draw_sprite *list, int i)
{
	t_enemy		*e;
	t_texture	*tex;
	double		depth;

	e = game->enemies;
	while (e)
	{
		if (e->x >= (double)w->min_x && e->x <= (double)w->max_x
			&& e->y >= (double)w->min_y && e->y <= (double)w->max_y)
		{
			tex = get_enemy_texture(game, e);
			depth = sprite_compute_depth(&game->player, e->x - 0.5, e->y - 0.5);
			if (tex && tex->img.img && depth > 0.0)
			{
				add_sprite_info(&list[i], e->x, e->y, depth);
				list[i].tex = &tex->img;
				i++;
			}
		}
		e = e->next;
	}
	return (i);
}
