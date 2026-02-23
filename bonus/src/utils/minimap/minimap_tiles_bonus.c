/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tiles_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "libft.h"
#include "minimap_bonus.h"
#include "render_bonus.h"

/**
 * ENGLISH: Checks if any of the 8 neighbours of (x, y) is a floor tile.
 *          Used to decide whether a wall tile should be drawn on the minimap.
 *
 * SPANISH: Comprueba si alguno de los 8 vecinos de (x, y) es una casilla
 *          de suelo. Sirve para decidir si un muro se dibuja en el minimapa.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Map column index. / Índice de columna del mapa.
 * @param y Map row index. / Índice de fila del mapa.
 *
 * @return 1 if a floor neighbour exists, 0 otherwise. /
 *         1 si existe vecino de suelo, 0 en caso contrario.
 */
int	has_floor_nearby(t_game *game, int x, int y)
{
	int	dx;
	int	dy;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (y + dy >= 0 && y + dy < game->map.height)
				if (x + dx >= 0 && game->map.grid[y + dy])
					if (x + dx < (int)ft_strlen(game->map.grid[y + dy]))
						if (game->map.grid[y + dy][x + dx] == '0')
							return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

/**
 * ENGLISH: Converts world coordinates into a map tile and draws the
 *          corresponding minimap colour at pixel (px, py).
 *
 * SPANISH: Convierte coordenadas del mundo en una casilla del mapa y
 *          dibuja el color de minimapa correspondiente en el píxel (px,py).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param px Destination pixel X in the minimap. /
 *           Píxel X destino en el minimapa.
 * @param py Destination pixel Y in the minimap. /
 *           Píxel Y destino en el minimapa.
 * @param world World float coordinates. / Coordenadas flotantes del mundo.
 */
void	put_minimap_tile(t_game *game, int px, int py, t_fcoord world)
{
	int	map_x;
	int	map_y;

	map_x = (int)world.x;
	map_y = (int)world.y;
	if (map_y >= 0 && map_y < game->map.height && map_x >= 0
		&& game->map.grid[map_y]
		&& map_x < (int)ft_strlen(game->map.grid[map_y]))
	{
		if (game->map.grid[map_y][map_x] == '1' && has_floor_nearby(game, map_x,
				map_y))
			img_pixel_put(&game->minimap, px, py, MINIMAP_WALL_COLOR);
		else if (game->map.grid[map_y][map_x] == 'D')
			img_pixel_put(&game->minimap, px, py, MINIMAP_DOOR_COLOR);
		else if (game->map.grid[map_y][map_x] == 'A')
			img_pixel_put(&game->minimap, px, py, MINIMAP_EXIT_COLOR);
		else
			img_pixel_put(&game->minimap, px, py, MINIMAP_FLOOR_COLOR);
	}
}
