/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_append_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:31 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 01:24:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sprite_helpers_bonus.h"

#ifndef SPRITE_NEAR_CLIP
# define SPRITE_NEAR_CLIP 0.05
#endif

double	sprite_compute_depth(t_game *game, double sx, double sy)
{
	double	spr_x;
	double	spr_y;
	double	inv_det;
	double	transform_y;

	spr_x = sx + 0.5 - game->player.pos_x;
	spr_y = sy + 0.5 - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_y = inv_det * (-game->player.plane_y * spr_x
			+ game->player.plane_x * spr_y);
	if (transform_y > SPRITE_NEAR_CLIP)
		return (transform_y);
	return (0.0);
}

static void	add_sprite(t_draw_sprite *new_sprite, double x, double y,
		t_img *tex, double depth)
{
	new_sprite->x = x + 0.5;
	new_sprite->y = y + 0.5;
	new_sprite->depth = depth;
	new_sprite->tex = tex;
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
			if (ft_strchr("X01NSEW", tile))
				continue ;
			tex = sprite_get_texture(game, tile);
			depth = sprite_compute_depth(game, x, y);
			if (tex && tex->img.img && depth > 0.0)
			{
				add_sprite(&list[i], x, y, &tex->img, depth);
				i++;
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
			depth = sprite_compute_depth(game, e->x, e->y);
			if (tex && tex->img.img && depth > 0.0)
			{
				add_sprite(&list[i], e->x, e->y, &tex->img, depth);
				i++;
			}
		}
		e = e->next;
	}
	return (i);
}
