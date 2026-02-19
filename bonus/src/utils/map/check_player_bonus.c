/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:15:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "map_bonus.h"
#include "player_bonus.h"
#include "console_bonus.h"

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
			player_count += is_player_char(map[i][j++]);
	}
	if (player_count != 1)
	{
		ft_fprintf(2, RED "Error: %d players found. ", player_count);
		ft_fprintf(2, RED "Only one of N, S, E or W is allowed\n" RESET);
		return (-1);
	}
	return (0);
}
