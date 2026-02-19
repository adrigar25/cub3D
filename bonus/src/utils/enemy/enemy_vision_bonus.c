/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_vision_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:20:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

static int	is_blocking_tile(t_game *game, int mx, int my)
{
	char	c;

	if (my < 0 || my >= game->map.height || mx < 0)
		return (1);
	if (!game->map.grid[my])
		return (1);
	if (mx >= (int)ft_strlen(game->map.grid[my]))
		return (1);
	c = game->map.grid[my][mx];
	return (c == '1' || c == 'D' || c == 'A');
}

static int	check_los_step(t_game *game, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (is_blocking_tile(game, mx, my))
		return (0);
	return (1);
}

static int	has_clear_los(t_game *game, double x0, double y0, t_enemy *e)
{
	double	dx;
	double	dy;
	double	dist;
	int		steps;
	int		i;

	dx = e->x - x0;
	dy = e->y - y0;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 1e-6)
		return (1);
	steps = (int)(dist / 0.1);
	i = 1;
	while (i <= steps)
	{
		if (!check_los_step(game, x0 + (dx / dist) * (i * 0.1), y0 + (dy / dist)
				* (i * 0.1)))
			return (0);
		i++;
	}
	return (1);
}

int	enemy_can_see_player(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;
	double	dist;

	if (!game || !e)
		return (0);
	dx = e->x - game->player.pos_x;
	dy = e->y - game->player.pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > ENEMY_AGGRO_RANGE_TILES)
		return (0);
	if (!has_clear_los(game, game->player.pos_x, game->player.pos_y, e))
		return (0);
	return (1);
}
