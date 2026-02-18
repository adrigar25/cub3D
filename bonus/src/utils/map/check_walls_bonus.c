/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 01:11:22 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	get_direction(int i, int *dx, int *dy)
{
	if (i == 0 || i == 4 || i == 5)
		*dx = 1;
	if (i == 1 || i == 6 || i == 7)
		*dx = -1;
	if (i == 2 || i == 4 || i == 6)
		*dy = 1;
	else if (i == 3 || i == 5 || i == 7)
		*dy = -1;
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

int	check_directions(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!is_valid_neighbor(map, x, y, i))
			return (-1);
		i++;
	}
	return (1);
}

int	check_walls(char **map)
{
	int	x;
	int	y;

	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (!(map[x][y] == '0' || is_player_char(map[x][y])
					|| map[x][y] == 'D' || map[x][y] == 'C'))
				continue ;
			if (check_directions(map, x, y) == -1)
			{
				ft_fprintf(2, RED "Error: Open wall or hole");
				ft_fprintf(2, "at row %d, col %d\n" RESET, x + 1, y + 1);
				return (-1);
			}
		}
	}
	return (1);
}
