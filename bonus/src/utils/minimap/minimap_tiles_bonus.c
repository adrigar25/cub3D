/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tiles_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	has_floor_nearby(t_game *game, int x, int y) {
  int dx;
  int dy;

  dy = -1;
  while (dy <= 1) {
    dx = -1;
    while (dx <= 1) {
      if (y + dy >= 0 && y + dy < game->map_h && x + dx >= 0 &&
          game->map[y + dy] && x + dx < (int)ft_strlen(game->map[y + dy]) &&
          game->map[y + dy][x + dx] == '0')
        return (1);
      dx++;
    }
    dy++;
  }
  return (0);
}

void	put_minimap_tile(t_game *game, int px, int py, double world_x) {
  int map_x;
  int map_y;

  map_x = (int)world_x;
  map_y = (int)game->player.pos_y;
  if (map_y >= 0 && map_y < game->map_h && map_x >= 0 && game->map[map_y] &&
      map_x < (int)ft_strlen(game->map[map_y])) {
    if (game->map[map_y][map_x] == '1' && has_floor_nearby(game, map_x, map_y))
      img_pixel_put(&game->minimap, px, py, MINIMAP_WALL_COLOR);
    else if (game->map[map_y][map_x] == 'D')
      img_pixel_put(&game->minimap, px, py, MINIMAP_DOOR_COLOR);
    else
      img_pixel_put(&game->minimap, px, py, MINIMAP_FLOOR_COLOR);
  }
}
