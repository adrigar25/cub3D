/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/11 18:30:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	get_direction(int i, int *dx, int *dy)
{
	if (i == 0)
		*dx = 1;
	else if (i == 1)
		*dx = -1;
	else if (i == 2)
		*dy = 1;
	else if (i == 3)
		*dy = -1;
	else if (i == 4)
	{
		*dx = 1;
		*dy = 1;
	}
	else if (i == 5)
	{
		*dx = 1;
		*dy = -1;
	}
	else if (i == 6)
	{
		*dx = -1;
		*dy = 1;
	}
	else if (i == 7)
	{
		*dx = -1;
		*dy = -1;
	}
}
static int	is_valid_neighbor(char **map, int x, int y, int i)
{
	int	new_x;
	int	new_y;
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	get_direction(i, &dx, &dy);
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
	return (1);
}

int	check_walls(char **map)
{
	int	i;
	int	x;
	int	y;

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
				if (!is_valid_neighbor(map, x, y, i))
					return (-1);
		}
	}
	return (0);
}
