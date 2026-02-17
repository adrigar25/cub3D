/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "minimap_bonus.h"

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
