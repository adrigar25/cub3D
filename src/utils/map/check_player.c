/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:15:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/07 15:56:26 by agarcia          ###   ########.fr       */
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
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				player_count++;
		}
	}
	if (player_count == 0)
		return (ft_error("check_player", (char *[]){"No player found", NULL}),
			-1);
	if (player_count > 1)
		return (ft_error("check_player", (char *[]){"Multiple players found",
				NULL}), -1);
	return (0);
}
