/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "render_bonus.h"
#include "sprite_bonus.h"
#include <math.h>

/**
 * ENGLISH: Computes the on-screen pixel height and width for a sprite
 *          given its texture dimensions and projection depth.
 *
 * SPANISH: Calcula la altura y anchura en píxeles en pantalla para un
 *          sprite dado las dimensiones de su textura y la profundidad
 *          de proyección.
 *
 * @param texture Pointer to the sprite texture. /
 *                Puntero a la textura del sprite.
 * @param transform_y Projection depth. / Profundidad de proyección.
 * @param height Output screen height. / Altura en pantalla de salida.
 * @param width Output screen width. / Anchura en pantalla de salida.
 */
void	sprite_compute_size(t_img *texture, double transform_y, int *height,
		int *width)
{
	*height = (int)fabs(WIN_H / transform_y);
	if (texture->height > 0)
		*width = (int)((double)*height * (double)texture->width
				/ (double)texture->height);
	else
		*width = *height;
	if (*height < 1)
		*height = 1;
	if (*width < 1)
		*width = 1;
}

/**
 * ENGLISH: Computes the vertical draw bounds for a sprite column,
 *          clamping to screen edges and storing the original top edge.
 *
 * SPANISH: Calcula los límites verticales de dibujo para una columna
 *          de sprite, limitando a los bordes de pantalla y guardando
 *          el borde superior original.
 *
 * @param height Sprite screen height. / Altura en pantalla del sprite.
 * @param screen_x Screen X column (unused, reserved). /
 *                 Columna X de pantalla (no usada, reservada).
 * @param pitch Player vertical pitch offset. /
 *              Desplazamiento vertical del jugador.
 * @param b Output bounds structure. / Estructura de límites de salida.
 */
void	sprite_compute_y_bounds(int height, int screen_x, int pitch,
		t_sprite_bounds *b)
{
	double	y0;
	double	y1;

	y0 = -height / 2.0 + WIN_H / 2.0 + pitch;
	y1 = height / 2.0 + WIN_H / 2.0 + pitch;
	b->draw_start_y = (int)y0;
	b->draw_end_y = (int)y1;
	if (b->draw_start_y < 0)
		b->draw_start_y = 0;
	if (b->draw_end_y >= WIN_H)
		b->draw_end_y = WIN_H - 1;
	b->y0 = y0;
	b->sprite_height = height;
	(void)screen_x;
}

/**
 * ENGLISH: Computes the horizontal draw bounds for a sprite, clamped to
 *          screen edges, and stores the original left edge for texturing.
 *
 * SPANISH: Calcula los límites horizontales de dibujo para un sprite,
 *          limitados a los bordes de pantalla, y guarda el borde izquierdo
 *          original para el texturizado.
 *
 * @param width Sprite screen width. / Anchura en pantalla del sprite.
 * @param screen_x Screen centre X column. / Columna X central en pantalla.
 * @param scr_out Output screen X. / X de pantalla de salida.
 * @param b Output bounds structure. / Estructura de límites de salida.
 */
void	sprite_compute_x_bounds(int width, int screen_x, int *scr_out,
		t_sprite_bounds *b)
{
	b->draw_start_x = -width / 2 + screen_x;
	b->draw_start_x_orig = b->draw_start_x;
	if (b->draw_start_x < 0)
		b->draw_start_x = 0;
	b->draw_end_x = width / 2 + screen_x;
	if (b->draw_end_x >= WIN_W)
		b->draw_end_x = WIN_W - 1;
	b->sprite_width = width;
	*scr_out = screen_x;
}
