/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_put_image_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/07 18:06:35 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"
#include "minimap_bonus.h"

static void	calc_minimap_pos(t_game *game, int map_x, int map_y, int *px,
		int *py)
{
	double	c;
	double	s;
	double	dx;
	double	dy;

	c = game->minimap.width / 2.0;
	s = MINIMAP_SCALE / 2.0;
	dx = (double)map_x + 0.5 - game->player.pos_x;
	dy = (double)map_y + 0.5 - game->player.pos_y;
	*px = (int)(c + s * (dx * game->player.dir_y - dy * game->player.dir_x));
	*py = (int)(c - s * (dx * game->player.dir_x + dy * game->player.dir_y));
}

static void	calc_img_dims(t_img *image, int px, int py, t_minimap_dims *d)
{
	d->px_center = px;
	d->py_center = py;
	d->target_w = (int)(MINIMAP_SCALE / 2.0);
	if (d->target_w > image->width)
		d->target_w = image->width;
	d->target_h = (int)((double)image->height * d->target_w
			/ (double)image->width);
	if (d->target_h < 1)
		d->target_h = 1;
	d->start_x = px - d->target_w / 2;
	d->start_y = py - d->target_h / 2;
}

static int	get_pixel_color(t_img *image, int src_x, int src_y)
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	char			*src;

	src = image->addr + (src_y * image->line_len + src_x * (image->bpp / 8));
	if (image->endian)
	{
		a = (unsigned char)src[0];
		r = (unsigned char)src[1];
		g = (unsigned char)src[2];
		b = (unsigned char)src[3];
	}
	else
	{
		b = (unsigned char)src[0];
		g = (unsigned char)src[1];
		r = (unsigned char)src[2];
		a = (unsigned char)src[3];
	}
	if (a == 0)
		return (-1);
	return (((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b);
}

static void	draw_pixel_if_in_circle(t_game *game, t_img *image, int ix, int iy,
		const t_minimap_dims *d)
{
	int		tx;
	int		ty;
	int		color;
	int		src_x;
	int		src_y;
	double	dist;
	double	cx;
	double	cy;
	double	radius;

	ty = d->start_y + iy;
	tx = d->start_x + ix;
	if (ty < 0 || ty >= game->minimap.height || tx < 0
		|| tx >= game->minimap.width)
		return ;
	cx = game->minimap.width / 2.0;
	cy = game->minimap.height / 2.0;
	radius = cx;
	dist = sqrt((tx - cx) * (tx - cx) + (ty - cy) * (ty - cy));
	if (dist > radius - MINIMAP_BORDER)
		return ;
	src_x = (int)((double)ix * image->width / d->target_w);
	src_y = (int)((double)iy * image->height / d->target_h);
	color = get_pixel_color(image, src_x, src_y);
	if (color != -1)
		img_pixel_put(&game->minimap, tx, ty, color);
}

void	minimap_put_image_at(t_game *game, t_img *image, int map_x, int map_y)
{
	t_minimap_dims	dims;
	int				px;
	int				py;
	int				ix;
	int				iy;

	if (!game || !image || !image->img)
		return ;
	calc_minimap_pos(game, map_x, map_y, &px, &py);
	calc_img_dims(image, px, py, &dims);
	iy = 0;
	while (iy < dims.target_h)
	{
		ix = 0;
		while (ix < dims.target_w)
		{
			draw_pixel_if_in_circle(game, image, ix, iy, &dims);
			ix++;
		}
		iy++;
	}
}
