/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:15:32 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math_utils.h"

/**
 * ENGLISH: Check if a position (x, y) is valid (not a wall).
 *
 * SPANISH: Comprueba si una posición (x, y) es válida (no está fuera del mapa).
 */
int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)clamp(x, 0, 10000);
	map_y = (int)clamp(y, 0, 10000);
	if (is_out_of_bounds(map_x, map_y, game->map))
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	return (1);
}
