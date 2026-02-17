/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_validation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:17 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * ENGLISH: Check if a position (x, y) is valid (not a wall).
 *
 * SPANISH: Comprueba si una posición (x, y) es válida (no es una pared).
 */
int	is_valid_position(t_game *game, double x, double y)
{
	double	margin;
	int		map_x;
	int		map_y;

	margin = PLAYER_HITBOX;
	if (ft_strchr("1D", game->map[(int)(y - margin)][(int)(x - margin)]))
		return (0);
	if (ft_strchr("1D", game->map[(int)(y - margin)][(int)(x + margin)]))
		return (0);
	if (ft_strchr("1D", game->map[(int)(y + margin)][(int)(x - margin)]))
		return (0);
	if (ft_strchr("1D", game->map[(int)(y + margin)][(int)(x + margin)]))
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (0);
	if (!game->map[map_y] || !game->map[map_y][map_x])
		return (0);
	if (ft_strchr("1D", game->map[map_y][map_x]))
		return (0);
	return (1);
}
