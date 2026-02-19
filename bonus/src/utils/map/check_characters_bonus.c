/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "map_bonus.h"
#include "console_bonus.h"

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

	if (!game || !game->map.grid)
		return (-1);
	i = -1;
	while (game->map.grid[++i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_allowed_char(game, game->map.grid[i][j]))
			{
				ft_fprintf(2, RED "Error: Invalid character '%c'");
				ft_fprintf(2, " at row %d, col %d\n" RESET, game->map.grid[i][j], i
					+ 1, j + 1);
				return (-1);
			}
			j++;
		}
	}
	return (0);
}
