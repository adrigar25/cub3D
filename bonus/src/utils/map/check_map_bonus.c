/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "map_bonus.h"
#include "console_bonus.h"

static int	has_exit(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'A')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_game *game)
{
	char	**map;

	if (game)
		map = game->map.grid;
	else
		map = NULL;
	if (!map || !map[0] || !map[0][0])
		return (ft_fprintf(2, RED "Error: Map is empty\n" RESET), -1);
	if (check_empty_rows(map) == -1)
		return (-1);
	if (check_empty_columns(map) == -1)
		return (-1);
	if (check_valid_characters(game) == -1)
		return (-1);
	if (check_player(map) == -1)
		return (-1);
	if (check_walls(map) == -1)
		return (-1);
	if (!has_exit(map))
		return (ft_fprintf(2, RED "Error: Map has no exit (A)\n" RESET), -1);
	if (!game->txt_exit)
		return (ft_fprintf(2,
				RED "Error: Exit texture (A) not defined\n" RESET), -1);
	return (0);
}
