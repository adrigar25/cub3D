/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 15:25:17 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_valid_neighbor(char **map, int x, int y, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = x + dx;
	new_y = y + dy;
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

static int	check_walls(char **map, int x, int y)
{
	static int	dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1},
			{-1, 1}, {-1, -1}};
	int			i;

	if (!(map[x][y] == '0' || ft_strchr("NSEW", map[x][y])))
		return (0);
	i = -1;
	while (++i < 8)
		if (!is_valid_neighbor(map, x, y, dir[i][0], dir[i][1]))
			return (-1);
	return (0);
}

static int	check_empty_rows(char **map, int *max_len)
{
	int	i;
	int	j;
	int	all_spaces;

	i = -1;
	*max_len = 0;
	while (map[++i])
	{
		j = -1;
		all_spaces = 1;
		while (map[i][++j])
		{
			if (ft_strchr(" \t", map[i][j]) == NULL)
			{
				all_spaces = 0;
				break ;
			}
		}
		if (all_spaces)
			return (-1);
		if (j > *max_len)
			*max_len = j;
	}
	return (0);
}

static int	check_empty_columns(char **map, int max_len)
{
	int	i;
	int	j;
	int	all_spaces;

	j = -1;
	while (++j < max_len)
	{
		i = -1;
		all_spaces = 1;
		while (map[++i])
		{
			if (j < (int)ft_strlen(map[i]) && ft_strchr(" \t",
					map[i][j]) == NULL)
			{
				all_spaces = 0;
				break ;
			}
		}
		if (all_spaces)
			return (-1);
	}
	return (0);
}

int	check_empty(char **map)
{
	int	max_len;

	if (check_empty_rows(map, &max_len) == -1)
		return (-1);
	if (check_empty_columns(map, max_len) == -1)
		return (-1);
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (ft_error("check_map",
			(char *[]){"Map is NULL", NULL}));
	if (check_empty(map) == -1)
		return (ft_error("check_map",
			(char *[]){"Map has empty lines", NULL}));
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(" 01NSEW\n", map[i][j]) == NULL)
					return (ft_error("check_map",
						(char *[]){"Invalid character in map", NULL}));
			if (check_walls(map, i, j) == -1)
				return (ft_error("check_map",
					(char *[]){"Map not closed", NULL}));
			j++;
		}
		i++;
	}
	return (0);
}
