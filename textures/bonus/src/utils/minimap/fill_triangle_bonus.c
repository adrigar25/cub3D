/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "render_bonus.h"
#include "minimap_bonus.h"

/**
 * ENGLISH: Draws a horizontal line of MINIMAP_PLAYER_COLOR pixels from
 *          x_start to x_end at scanline y.
 *
 * SPANISH: Dibuja una línea horizontal de píxeles MINIMAP_PLAYER_COLOR
 *          desde x_start hasta x_end al nivel de escaneado y.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x_start Start X coordinate. / Coordenada X de inicio.
 * @param x_end End X coordinate. / Coordenada X de fin.
 * @param y Scanline row. / Fila de escaneado.
 */
void	draw_horizontal_line(t_game *game, int x_start, int x_end, int y)
{
	int	x;
	int	tmp;

	if (x_start > x_end)
	{
		tmp = x_start;
		x_start = x_end;
		x_end = tmp;
	}
	x = x_start;
	while (x <= x_end)
	{
		if (x >= 0 && x < game->minimap.width && y >= 0
			&& y < game->minimap.height)
			img_pixel_put(&game->minimap, x, y, MINIMAP_PLAYER_COLOR);
		x++;
	}
}

/**
 * ENGLISH: Fills a flat-bottom triangle using scanline rasterisation.
 *          Vertices must be sorted so that y1 <= y2 == y3.
 *
 * SPANISH: Rellena un triángulo con base plana inferior usando
 *          rasterización por líneas de barrido. Los vértices deben estar
 *          ordenados de forma que y1 <= y2 == y3.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param tri Pointer to the triangle to fill. /
 *            Puntero al triángulo a rellenar.
 */
void	fill_bottom_triangle(t_game *game, const t_triangle *tri)
{
	double	inv_slope1;
	double	inv_slope2;
	double	cur_x1;
	double	cur_x2;
	int		scanline_y;

	inv_slope1 = (double)(tri->x2 - tri->x1) / (tri->y2 - tri->y1);
	inv_slope2 = (double)(tri->x3 - tri->x1) / (tri->y3 - tri->y1);
	cur_x1 = tri->x1;
	cur_x2 = tri->x1;
	scanline_y = tri->y1;
	while (scanline_y <= tri->y2)
	{
		draw_horizontal_line(game, (int)cur_x1, (int)cur_x2, scanline_y);
		cur_x1 += inv_slope1;
		cur_x2 += inv_slope2;
		scanline_y++;
	}
}

/**
 * ENGLISH: Fills a flat-top triangle using scanline rasterisation.
 *          Vertices must be sorted so that y1 == y2 <= y3.
 *
 * SPANISH: Rellena un triángulo con base plana superior usando
 *          rasterización por líneas de barrido. Los vértices deben estar
 *          ordenados de forma que y1 == y2 <= y3.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param tri Pointer to the triangle to fill. /
 *            Puntero al triángulo a rellenar.
 */
void	fill_top_triangle(t_game *game, const t_triangle *tri)
{
	double	inv_slope1;
	double	inv_slope2;
	double	cur_x1;
	double	cur_x2;
	int		scanline_y;

	inv_slope1 = (double)(tri->x3 - tri->x1) / (tri->y3 - tri->y1);
	inv_slope2 = (double)(tri->x3 - tri->x2) / (tri->y3 - tri->y2);
	cur_x1 = tri->x3;
	cur_x2 = tri->x3;
	scanline_y = tri->y3;
	while (scanline_y > tri->y1)
	{
		draw_horizontal_line(game, (int)cur_x1, (int)cur_x2, scanline_y);
		cur_x1 -= inv_slope1;
		cur_x2 -= inv_slope2;
		scanline_y--;
	}
}
