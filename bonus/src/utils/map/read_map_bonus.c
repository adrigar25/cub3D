/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_allowed_char(t_game *game, char c) {
  int i;

  if (!game)
    return (0);
  i = 0;
  while (i < game->allowed_count) {
    if (game->allowed_chars[i] == c)
      return (1);
    i++;
  }
  return (0);
}

int	is_map_line(t_game *game, char *line) {
  int i;

  if (!line || !line[0] || line[0] == '\n')
    return (0);
  i = 0;
  while (line[i]) {
    if (!is_allowed_char(game, line[i]))
      return (0);
    i++;
  }
  return (1);
}

static int	add_line(t_game *game, int index, char *line, size_t *max_width) {
  char **new_map;

  if (!is_map_line(game, line)) {
    if (line)
      ft_fprintf(2, RED "Error: invalid map line: %s" RESET "\n", line);
    else
      ft_fprintf(2, RED "Error: invalid map line: (null)" RESET "\n");
    return (-1);
  }
  if (ft_strlen(line) > *max_width)
    *max_width = ft_strlen(line);
  new_map = ft_realloc(game->map, sizeof(char *) * index,
                       sizeof(char *) * (index + 2));
  if (!new_map)
    return (-1);
  game->map = new_map;
  game->map[index] = ft_strtrim(line, "\n");
  if (!game->map[index])
    return (-1);
  return (0);
}

int	read_map(t_game *game, int fd, char *first_line) {
  char *line;
  int i;
  size_t max_width;

  i = 0;
  max_width = 0;
  if (!first_line)
    return (-1);
  line = ft_strdup(first_line);
  free(first_line);
  while (1) {
    if (i > 0)
      line = ft_get_next_line(fd);
    if (!line)
      break ;
    if (add_line(game, i, line, &max_width) == -1)
      return (free(line), -1);
    free(line);
    i++;
  }
  game->map_h = i;
  game->map_w = (int)max_width;
  enemy_collect_from_map(game);
  return (0);
}
