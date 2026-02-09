/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::: ::::::::   */
/*   player_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 19:00:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"
#include "minimap_bonus.h"

extern t_triangle	create_triangle(int x1, int y1, int x2, int y2, int x3,
						int y3);
extern void			sort_triangle_vertices(t_triangle *tri);
extern void			fill_bottom_triangle(t_game *game, const t_triangle *tri);
extern void			fill_top_triangle(t_game *game, const t_triangle *tri);

t_triangle	player_triangle(double cx, double cy)
{
	double	arrow_len;
	double	base_width;
	double	offset_y;

	arrow_len = MINIMAP_PLAYER_SIZE * 2.5;
	base_width = MINIMAP_PLAYER_SIZE;
	offset_y = arrow_len / 3.0;
	return (create_triangle((int)cx, (int)(cy - arrow_len + offset_y), (int)(cx
				- base_width), (int)(cy + offset_y), (int)(cx + base_width),
			(int)(cy + offset_y)));
}

static void	fill_split(t_game *game, t_triangle *tri)
{
	t_triangle	bottom;
	t_triangle	top;
	int			x4;

	x4 = tri->x1 + ((double)(tri->y2 - tri->y1) / (tri->y3 - tri->y1))
		* (tri->x3 - tri->x1);
	bottom.x1 = tri->x1;
	bottom.y1 = tri->y1;
	bottom.x2 = tri->x2;
	bottom.y2 = tri->y2;
	bottom.x3 = x4;
	bottom.y3 = tri->y2;
	top.x1 = tri->x2;
	top.y1 = tri->y2;
	top.x2 = x4;
	top.y2 = tri->y2;
	top.x3 = tri->x3;
	top.y3 = tri->y3;
	fill_bottom_triangle(game, &bottom);
	fill_top_triangle(game, &top);
}

void	draw_player(t_game *game, double center_x, double center_y)
{
	t_triangle	tri;

	tri = player_triangle(center_x, center_y);
	sort_triangle_vertices(&tri);
	if (tri.y2 == tri.y3)
		fill_bottom_triangle(game, &tri);
	else if (tri.y1 == tri.y2)
		fill_top_triangle(game, &tri);
	else
		fill_split(game, &tri);
}
