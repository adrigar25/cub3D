/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_vision_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:20:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 00:53:14 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"
#include <math.h>

static int	is_blocking_tile(t_game *game, int mx, int my)
{
	char	c;

	if (my < 0 || my >= game->map_h || mx < 0)
		return (1);
	if (!game->map[my])
		return (1);
	if (mx >= (int)ft_strlen(game->map[my]))
		return (1);
	c = game->map[my][mx];
	return (c == '1' || c == 'D');
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
	steps = (int)(dist / ENEMY_VISION_STEP);
	i = 1;
	while (i <= steps)
	{
		if (is_blocking_tile(game, (int)(x0 + (dx / dist) * (i
						* ENEMY_VISION_STEP)), (int)(y0 + (dy / dist) * (i
						* ENEMY_VISION_STEP))))
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
	double	dot;
	double	half_fov_rad;

	if (!game || !e)
		return (0);
	dx = e->x - game->player.pos_x;
	dy = e->y - game->player.pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > ENEMY_AGGRO_RANGE_TILES)
		return (0);
	if (dist > 1e-6)
		dot = (dx * game->player.dir_x + dy * game->player.dir_y) / dist;
	else
		dot = 1.0;
	half_fov_rad = (ENEMY_FOV_DEG * M_PI / 180.0) / 2.0;
	if (dot < cos(half_fov_rad))
		return (0);
	if (!has_clear_los(game, game->player.pos_x, game->player.pos_y, e))
		return (0);
	return (1);
}
