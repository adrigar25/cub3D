/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:58:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "sprite_helpers_bonus.h"
#include <math.h>

static int	spr_is_transparent(t_img *texture, int color)
{
	if (!texture || !texture->addr)
		return (0);
	return ((unsigned int)color == (*(unsigned int *)texture->addr));
}

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
