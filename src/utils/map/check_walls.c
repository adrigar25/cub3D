/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/07 16:12:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_valid_neighbor(char **map, int x, int y, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = x + dx;
	new_y = y + dy;
	if (new_x < 0)
		return (0);
	if (!map[new_x])
		return (0);
	if (new_y < 0)
		return (0);
	if (new_y >= (int)ft_strlen(map[new_x]))
		return (0);
	if (ft_strchr(" \0", map[new_x][new_y]))
		return (0);
	if (ft_strchr("1", map[new_x][new_y]))
		return (1);
	return (0);
}

int	check_walls(char **map)
{
	static int	dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1},
			{-1, 1}, {-1, -1}};
	int			i;
	int			x;
	int			y;

	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (!(map[x][y] == '0' || ft_strchr("NSEW", map[x][y])))
				continue ;
			i = -1;
			while (++i < 8)
				if (!is_valid_neighbor(map, x, y, dir[i][0], dir[i][1]))
					return (-1);
		}
	}
	return (0);
}
