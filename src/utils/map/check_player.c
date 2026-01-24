/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:15:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/24 13:35:45 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_player(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && player_count <= 1)
			player_count += ft_strchr("NSEW", map[i][j++]) != NULL;
	}
	if (player_count == 0)
		return (ft_fprintf(2, RED "No player found" RESET "\n"), -1);
	if (player_count > 1)
		return (ft_fprintf(2, RED "Multiple players found" RESET "\n"), -1);
	return (0);
}
