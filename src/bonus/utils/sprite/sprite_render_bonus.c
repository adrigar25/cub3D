/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/07 00:37:01 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"
#include "../../sprite_helpers_bonus.h"

static int	spr_cmp_by_depth(const void *a, const void *b)
{
	const t_draw_sprite	*sa;
	const t_draw_sprite	*sb;

	sa = (const t_draw_sprite *)a;
	sb = (const t_draw_sprite *)b;
	if (sa->depth < sb->depth)
		return (1);
	if (sa->depth > sb->depth)
		return (-1);
	return (0);
}

static void	spr_render_sorted(t_game *game, t_draw_sprite *list, int count)
{
	int	i;

	qsort(list, count, sizeof(t_draw_sprite), spr_cmp_by_depth);
	i = 0;
	while (i < count)
	{
		sprite_draw_at(game, list[i].tex, list[i].x, list[i].y);
		i++;
	}
}

void	sprite_render(t_game *game)
{
	int				count;
	t_draw_sprite	*list;
	int				i;
	t_sprite_window	window;

	if (!game || !game->map)
		return ;
	sprite_compute_scan_window(game, &window);
	count = sprite_count_total_in_window(game, &window);
	if (count <= 0)
		return ;
	list = (t_draw_sprite *)malloc(sizeof(t_draw_sprite) * count);
	if (!list)
		return ;
	i = sprite_append_map_sprites(game, &window, list, 0);
	i = sprite_append_enemy_sprites(game, &window, list, i);
	if (i > 0)
		spr_render_sorted(game, list, i);
	free(list);
}
