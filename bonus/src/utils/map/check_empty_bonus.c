/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_max_len(char **map) {
  int max_len;
  int i;
  int current_len;
  int j;

  max_len = 0;
  i = 0;
  while (map[i]) {
    current_len = 0;
    j = 0;
    while (map[i][j]) {
      if (ft_strchr(" \t\n", map[i][j]) == NULL)
        current_len = j + 1;
      j++;
    }
    if (current_len > max_len)
      max_len = current_len;
    i++;
  }
  return (max_len);
}

static int	get_starting_column(char **map, int max_len) {
  int start;

  start = 0;
  while (start < max_len && map[0][start] && map[0][start] != '1')
    start++;
  return (start);
}

int	check_empty_rows(char **map) {
  int i;
  int j;

  i = -1;
  while (map[++i]) {
    j = 0;
    while (map[i][j] && ft_strchr(" \t\n", map[i][j]) != NULL)
      j++;
    if (map[i][j] == '\0')
      return (-1);
  }
  return (0);
}

int	check_empty_columns(char **map) {
  int i;
  int j;
  int max_len;

  max_len = get_max_len(map);
  j = get_starting_column(map, max_len) - 1;
  while (++j < max_len) {
    i = -1;
    while (map[++i] && j < (int)ft_strlen(map[i]))
      if (ft_strchr(" \t\n", map[i][j]) == NULL)
        break ;
    if (!map[i])
      return (-1);
  }
  return (0);
}
