/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_allowed_char(t_game *game, char c)
{
	int	i;

	if (!game)
		return (0);
	i = 0;
	while (i < game->allowed_count)
	{
		if (game->allowed_chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_characters(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map)
		return (-1);
	i = -1;
	while (game->map[++i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_allowed_char(game, game->map[i][j]))
				return (ft_fprintf(2,
					RED "Error: Invalid character '%c' at row %d, col %d\n"
					RESET, game->map[i][j], i + 1, j + 1), -1);
			j++;
		}
	}
	return (0);
}
