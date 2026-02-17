/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_map(t_game *game)
{
	char	**map;

	if (game)
		map = game->map;
	else
		map = NULL;
	if (!map || !map[0] || !map[0][0])
		return (ft_fprintf(2, RED "Error: Map is empty\n" RESET), -1);
	if (check_empty_rows(map) == -1)
		return (ft_fprintf(2, RED "Error: Map has empty lines\n" RESET), -1);
	if (check_empty_columns(map) == -1)
		return (ft_fprintf(2, RED "Error: Map has empty cols\n" RESET), -1);
	if (check_valid_characters(game) == -1)
		return (ft_fprintf(2, RED "Error: Invalid char in map\n" RESET), -1);
	if (check_player(map) == -1)
		return (-1);
	if (check_walls(map) == -1)
		return (ft_fprintf(2, RED "Error: Map not closed\n" RESET), -1);
	return (0);
}
