/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "sprite_helpers_bonus.h"
#include <math.h>

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
