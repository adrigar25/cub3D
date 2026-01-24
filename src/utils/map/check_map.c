/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/24 14:25:49 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_map(char **map)
{
	if (!map || !map[0] || !map[0][0])
		return (ft_fprintf(2, RED "Error: Map is empty" RESET "\n"), -1);
	if (check_empty_rows(map) == -1)
		return (ft_fprintf(2, RED "Error: Map has empty lines" RESET "\n"), -1);
	if (check_empty_columns(map) == -1)
		return (ft_fprintf(2, RED "Error: Map has empty cols" RESET "\n"), -1);
	if (check_valid_characters(map) == -1)
		return (ft_fprintf(2, RED "Error: Invalid char in map" RESET "\n"), -1);
	if (check_player(map) == -1)
		return (-1);
	if (check_walls(map) == -1)
		return (ft_fprintf(2, RED "Error: Map not closed" RESET "\n"), -1);
	return (0);
}
