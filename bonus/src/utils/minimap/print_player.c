/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:01:53 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/29 02:13:14 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_horizontal_line(t_game *game, int x_start, int x_end, int y,
		int color)
{
	int	x;

	if (x_start > x_end)
	{
		x = x_start;
		x_start = x_end;
		x_end = x;
	}
	x = x_start;
	while (x <= x_end)
	{
		if (x >= 0 && x < game->minimap.width && y >= 0
			&& y < game->minimap.height)
			img_pixel_put(&game->minimap, x, y, color);
		x++;
	}
}

static void	sort_vertices(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3)
{
	int	temp_x;
	int	temp_y;

	if (*y1 > *y2)
	{
		temp_x = *x1;
		*x1 = *x2;
		*x2 = temp_x;
		temp_y = *y1;
		*y1 = *y2;
		*y2 = temp_y;
	}
	if (*y1 > *y3)
	{
		temp_x = *x1;
		*x1 = *x3;
		*x3 = temp_x;
		temp_y = *y1;
		*y1 = *y3;
		*y3 = temp_y;
	}
	if (*y2 > *y3)
	{
		temp_x = *x2;
		*x2 = *x3;
		*x3 = temp_x;
		temp_y = *y2;
		*y2 = *y3;
		*y3 = temp_y;
	}
}

static void	fill_bottom_triangle(t_game *game, int x1, int y1, int x2, int y2,
		int x3, int y3)
{
	double	inv_slope1;
	double	inv_slope2;
	double	cur_x1;
	double	cur_x2;
	int		scanline_y;

	inv_slope1 = (double)(x2 - x1) / (y2 - y1);
	inv_slope2 = (double)(x3 - x1) / (y3 - y1);
	cur_x1 = x1;
	cur_x2 = x1;
	scanline_y = y1;
	while (scanline_y <= y2)
	{
		draw_horizontal_line(game, (int)cur_x1, (int)cur_x2, scanline_y,
			MINIMAP_PLAYER_COLOR);
		cur_x1 += inv_slope1;
		cur_x2 += inv_slope2;
		scanline_y++;
	}
}

static void	fill_top_triangle(t_game *game, int x1, int y1, int x2, int y2,
		int x3, int y3)
{
	double	inv_slope1;
	double	inv_slope2;
	double	cur_x1;
	double	cur_x2;
	int		scanline_y;

	inv_slope1 = (double)(x3 - x1) / (y3 - y1);
	inv_slope2 = (double)(x3 - x2) / (y3 - y2);
	cur_x1 = x3;
	cur_x2 = x3;
	scanline_y = y3;
	while (scanline_y > y1)
	{
		draw_horizontal_line(game, (int)cur_x1, (int)cur_x2, scanline_y,
			MINIMAP_PLAYER_COLOR);
		cur_x1 -= inv_slope1;
		cur_x2 -= inv_slope2;
		scanline_y--;
	}
}

void	draw_player(t_game *game, double center_x, double center_y)
{
	double	arrow_len;
	double	base_width;
	double	offset_y;
	int		x4;
	int		y4;
	int		v1_x;
	int		v1_y;
	int		v2_x;
	int		v2_y;
	int		v3_x;
	int		v3_y;

	arrow_len = MINIMAP_PLAYER_SIZE * 2.5;
	base_width = MINIMAP_PLAYER_SIZE;
	offset_y = arrow_len / 3.0;
	v1_x = center_x;
	v1_y = center_y - arrow_len + offset_y;
	v2_x = center_x - base_width;
	v2_y = center_y + offset_y;
	v3_x = center_x + base_width;
	v3_y = center_y + offset_y;
	sort_vertices(&v1_x, &v1_y, &v2_x, &v2_y, &v3_x, &v3_y);
	if (v2_y == v3_y)
		fill_bottom_triangle(game, v1_x, v1_y, v2_x, v2_y, v3_x, v3_y);
	else if (v1_y == v2_y)
		fill_top_triangle(game, v1_x, v1_y, v2_x, v2_y, v3_x, v3_y);
	else
	{
		x4 = v1_x + ((double)(v2_y - v1_y) / (v3_y - v1_y)) * (v3_x - v1_x);
		y4 = v2_y;
		fill_bottom_triangle(game, v1_x, v1_y, v2_x, v2_y, x4, y4);
		fill_top_triangle(game, v2_x, v2_y, x4, y4, v3_x, v3_y);
	}
}
