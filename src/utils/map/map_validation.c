/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/07 15:56:36 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_map(char **map)
{
	int	max_len;

	if (!map || !map[0] || !map[0][0])
		return (ft_error("check_map", (char *[]){"Map is empty", NULL}), -1);
	if (check_empty_rows(map, &max_len) == -1)
		return (ft_error("check_map", (char *[]){"Map has empty lines", NULL}),
			-1);
	if (check_empty_columns(map, max_len) == -1)
		return (ft_error("check_map", (char *[]){"Map has empty columns",
				NULL}), -1);
	if (check_valid_characters(map) == -1)
		return (ft_error("check_map", (char *[]){"Invalid character in map",
				NULL}), -1);
	if (check_player(map) == -1)
		return (-1);
	if (check_walls(map) == -1)
		return (ft_error("check_map", (char *[]){"Map not closed", NULL}), -1);
	return (0);
}
