/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/07 15:53:11 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_empty_rows(char **map, int *max_len)
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

int	check_empty_columns(char **map, int max_len)
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
			if (j >= (int)ft_strlen(map[i]))
				continue ;
			if (ft_strchr(" \t", map[i][j]) == NULL)
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
