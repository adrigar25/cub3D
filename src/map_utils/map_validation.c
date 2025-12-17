/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 00:35:44 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_walls(char **map, int x, int y)
{
	if (map[x][y] == '0' || ft_strchr("NSEW", map[x][y]))
	{
		if (!map[x + 1] || !map[x - 1] || !map[x][y + 1] || !map[x][y - 1])
			return (-1);
		if ((ft_strchr(" \0", map[x + 1][y]) != NULL) || (ft_strchr(" \0", map[x
					- 1][y]) != NULL) || (ft_strchr(" \0", map[x][y
					+ 1]) != NULL) || (ft_strchr(" \0", map[x][y - 1]) != NULL))
			return (-1);
		if (y + 1 < (int)ft_strlen(map[x + 1]) && ft_strchr(" \0", map[x + 1][y
				+ 1]) != NULL)
			return (-1);
		if (y - 1 >= 0 && y - 1 < (int)ft_strlen(map[x + 1]) && ft_strchr(" \0",
				map[x + 1][y - 1]) != NULL)
			return (-1);
		if (y + 1 < (int)ft_strlen(map[x - 1]) && ft_strchr(" \0", map[x - 1][y
				+ 1]) != NULL)
			return (-1);
		if (y - 1 >= 0 && y - 1 < (int)ft_strlen(map[x - 1]) && ft_strchr(" \0",
				map[x - 1][y - 1]) != NULL)
			return (-1);
	}
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
		return (handle_error("Map is NULL"));
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(" 01NSEW\n", map[i][j]) == NULL)
				return (handle_error("Invalid character in map"));
			if (check_walls(map, i, j) == -1)
				return (handle_error("Map not closed"));
			j++;
		}
		i++;
	}
	if (check_empty(map) == -1)
		return (handle_error("Map has empty lines"));
	return (0);
}
