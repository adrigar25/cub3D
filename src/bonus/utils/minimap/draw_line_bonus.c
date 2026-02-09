/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 19:04:25 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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
