/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:58:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "render_bonus.h"
#include "sprite_bonus.h"
#include <math.h>

/**
 * ENGLISH: Checks if the given colour is the transparent (key) colour
 *          stored at the very first byte of the texture image buffer.
 *
 * SPANISH: Comprueba si el color dado es el color transparente (clave)
 *          almacenado en el primer byte del buffer de imagen de la textura.
 *
 * @param texture Pointer to the texture. / Puntero a la textura.
 * @param color Colour value to test. / Valor de color a probar.
 *
 * @return 1 if transparent, 0 otherwise. /
 *         1 si es transparente, 0 en caso contrario.
 */
static int	spr_is_transparent(t_img *texture, int color)
{
	if (!texture || !texture->addr)
		return (0);
	return ((unsigned int)color == (*(unsigned int *)texture->addr));
}

/**
 * ENGLISH: Draws a vertical pixel column of a sprite at horizontal screen
 *          stripe, sampling the texture at the given tx coordinate.
 *
 * SPANISH: Dibuja una columna vertical de píxeles de un sprite en la
 *          franja horizontal de pantalla, muestreando la textura en la
 *          coordenada tx dada.
 *
 * @param ctx Sprite draw context. / Contexto de dibujo del sprite.
 * @param stripe Screen column X. / Columna X de pantalla.
 * @param tx Texture X coordinate. / Coordenada X de textura.
 * @param ys Texture Y step per screen pixel. /
 *           Paso de textura Y por píxel de pantalla.
 */
static void	spr_draw_pixel(t_sprite_ctx *ctx, int stripe, double tx, double ys)
{
	int	y;
	int	ty;
	int	color;

	if (tx < 0 || tx >= ctx->tex->width)
		return ;
	y = ctx->b.draw_start_y;
	while (y <= ctx->b.draw_end_y)
	{
		ty = (int)(((double)y - ctx->b.y0) * ys);
		if (ty >= 0 && ty < ctx->tex->height)
		{
			color = get_texture_color(ctx->tex, tx, ty);
			if (!spr_is_transparent(ctx->tex, color))
				img_pixel_put(&ctx->game->img, stripe, y, color);
		}
		y++;
	}
}

/**
 * ENGLISH: Iterates over all horizontal stripes of the sprite, skipping
 *          those behind a wall (z-buffer check), and draws each column.
 *
 * SPANISH: Itera sobre todas las franjas horizontales del sprite,
 *          omitiendo las que están detrás de una pared (comprobación
 *          z-buffer), y dibuja cada columna.
 *
 * @param ctx Sprite draw context. / Contexto de dibujo del sprite.
 */
static void	spr_draw_columns(t_sprite_ctx *ctx)
{
	int		stripe;
	double	tx;
	double	ys;

	stripe = ctx->b.draw_start_x;
	ys = (double)ctx->tex->height / (double)ctx->b.sprite_height;
	while (stripe <= ctx->b.draw_end_x)
	{
		if (ctx->ty < ctx->game->zbuffer[stripe])
		{
			tx = (double)(stripe - ctx->b.draw_start_x_orig) * ctx->tex->width
				/ (double)ctx->b.sprite_width;
			spr_draw_pixel(ctx, stripe, tx, ys);
		}
		stripe++;
	}
}

/**
 * ENGLISH: Projects and draws a sprite at the given world position,
 *          computing screen size and bounds before rendering each column.
 *
 * SPANISH: Proyecta y dibuja un sprite en la posición del mundo dada,
 *          calculando el tamaño y límites en pantalla antes de renderizar
 *          cada columna.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param texture Pointer to the sprite texture image. /
 *                Puntero a la imagen de textura del sprite.
 * @param world_x World X position of the sprite. /
 *                Posición X del sprite en el mundo.
 * @param world_y World Y position of the sprite. /
 *                Posición Y del sprite en el mundo.
 */
void	sprite_draw_at(t_game *game, t_img *texture, double world_x,
		double world_y)
{
	t_sprite_ctx	ctx;
	int				scx;
	int				h;
	int				w;

	ctx.ty = (1.0 / (game->player.plane_x * game->player.dir_y
				- game->player.dir_x * game->player.plane_y))
		* (-game->player.plane_y * (world_x - game->player.pos_x)
			+ game->player.plane_x * (world_y - game->player.pos_y));
	if (ctx.ty <= 0.0001)
		return ;
	scx = (int)((WIN_W / 2.0) * (1 + ((1.0 / (game->player.plane_x
							* game->player.dir_y - game->player.dir_x
							* game->player.plane_y)) * (game->player.dir_y
						* (world_x - game->player.pos_x) - game->player.dir_x
						* (world_y - game->player.pos_y))) / ctx.ty));
	sprite_compute_size(texture, ctx.ty, &h, &w);
	sprite_compute_y_bounds(h, scx, game->player.pitch, &ctx.b);
	sprite_compute_x_bounds(w, scx, &scx, &ctx.b);
	ctx.game = game;
	ctx.tex = texture;
	spr_draw_columns(&ctx);
}
