/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_create_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 00:57:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_enemy_coords(t_enemy *e, int tile_x, int tile_y)
{
	e->tile_x = tile_x;
	e->tile_y = tile_y;
	e->x = (float)tile_x + 0.5f;
	e->y = (float)tile_y + 0.5f;
}

t_enemy	*create_enemy(int tile_x, int tile_y)
{
	t_enemy	*e;

	e = (t_enemy *)malloc(sizeof(t_enemy));
	if (!e)
		return (NULL);
	e->next = NULL;
	set_enemy_coords(e, tile_x, tile_y);
	e->last_x = e->x;
	e->last_y = e->y;
	e->moving = 0;
	e->anim_frame = 0;
	e->anim_timer = 0;
	return (e);
}
