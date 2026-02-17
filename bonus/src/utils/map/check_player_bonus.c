/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:15:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_player(char **map) {
  int i;
  int j;
  int player_count;

  player_count = 0;
  i = -1;
  while (map[++i]) {
    j = 0;
    while (map[i][j] && player_count <= 1)
      player_count += is_player_char(map[i][j++]);
  }
  if (player_count == 0)
    return (ft_fprintf(2, RED "Error: No player found\n" RESET), -1);
  if (player_count > 1)
    return (ft_fprintf(2, RED "Error: Multiple players found\n" RESET), -1);
  return (0);
}
