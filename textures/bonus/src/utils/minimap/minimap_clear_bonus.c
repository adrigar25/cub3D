/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_clear_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/03/06 13:52:28 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "minimap_bonus.h"
#include "render_bonus.h"
#include <math.h>

/**
 * ENGLISH: Sets the colour of a single minimap pixel: transparent outside
 *          the circle, border colour in the ring, wall colour inside.
 *
 * SPANISH: Establece el color de un píxel del minimapa: transparente fuera
 *          del círculo, color de borde en el anillo, color de muro dentro.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Pixel column. / Columna del píxel.
 * @param y Pixel row. / Fila del píxel.
 * @param c Array [cx, cy] with the circle centre. /
 *          Array [cx, cy] con el centro del círculo.
 */
static void	clear_pixel(t_game *game, int x, int y, double *c)
{
	double	dist;

	dist = sqrt((x - c[0]) * (x - c[0]) + (y - c[1]) * (y - c[1]));
	if (dist > c[0])
		img_pixel_put(&game->minimap, x, y, 0xFF000000);
	else if (dist > c[0] - MINIMAP_BORDER)
		img_pixel_put(&game->minimap, x, y, MINIMAP_BORDER_COLOR);
	else
		img_pixel_put(&game->minimap, x, y, MINIMAP_WALL_COLOR);
}

/**
 * ENGLISH: Resets every pixel of the minimap image buffer to its default
 *          background state (border ring + wall fill).
 *
 * SPANISH: Restablece cada píxel del buffer de imagen del minimapa a su
 *          estado de fondo por defecto (anillo de borde + relleno de muro).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	clear_map(t_game *game)
{
	int		x;
	int		y;
	double	c[2];

	c[0] = game->minimap.width / 2.0;
	c[1] = game->minimap.height / 2.0;
	y = -1;
	while (++y < game->minimap.height)
	{
		x = -1;
		while (++x < game->minimap.width)
			clear_pixel(game, x, y, c);
	}
}
