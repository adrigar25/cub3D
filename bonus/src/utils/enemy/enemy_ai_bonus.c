/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:30 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	enemy_try_move(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;
	double	dist;
	double	scale;

	dx = game->player.pos_x - e->x;
	dy = game->player.pos_y - e->y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.0001 && dist <= ENEMY_AGGRO_RANGE_TILES
		&& enemy_can_see_player(game, e))
	{
		scale = ENEMY_SPEED / dist;
		dx *= scale;
		dy *= scale;
		if (is_valid_position(game, e->x + dx, e->y))
			e->x += dx;
		if (is_valid_position(game, e->x, e->y + dy))
			e->y += dy;
	}
}

static void	enemy_update_anim(t_enemy *e, double prev_x, double prev_y)
{
	if (fabs(e->x - prev_x) + fabs(e->y - prev_y) > 1e-5)
	{
		e->moving = 1;
		e->anim_timer++;
		if (e->anim_timer >= ENEMY_ANIM_SPEED_FRAMES)
		{
			e->anim_timer = 0;
			e->anim_frame ^= 1;
		}
	}
	else
	{
		e->moving = 0;
		e->anim_timer = 0;
		e->anim_frame = 0;
	}
	e->last_x = e->x;
	e->last_y = e->y;
}

void	enemy_update_ai(t_game *game)
{
	t_enemy	*e;
	double	prev_x;
	double	prev_y;

	if (!game)
		return ;
	e = game->enemies;
	while (e)
	{
		prev_x = e->x;
		prev_y = e->y;
		enemy_try_move(game, e);
		enemy_update_anim(e, prev_x, prev_y);
		e = e->next;
	}
}
