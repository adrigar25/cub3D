/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/06 16:51:19 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include "../math/math_utils.h"

static void	calculate_texture_coords(t_game *game, t_img *texture)
{
	double	impact;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;

	impact = calc_wall_impact(game->player, game->raycast);
	wall_x = clamp(fract(impact), 0.0, 1.0);
	if (game->raycast.side == 0)
		tex_x = calc_texture_x_coord(wall_x, game->raycast.side,
				game->raycast.ray_dir_x, texture->width);
	else
		tex_x = calc_texture_x_coord(wall_x, game->raycast.side,
				game->raycast.ray_dir_y, texture->width);
	step = safe_div((double)texture->height, game->raycast.line_height, 1.0);
	tex_pos = (game->raycast.draw_start - WIN_H / 2 + game->raycast.line_height
			/ 2) * step;
	game->raycast.wall_x = wall_x;
	game->raycast.tex_x = tex_x;
	game->raycast.step = step;
	game->raycast.tex_pos = tex_pos;
}

static t_img	*get_wall_texture(t_game *game)
{
	if (game->raycast.side == 0)
	{
		if (game->raycast.ray_dir_x > 0)
			return (&game->textures.ea);
		else
			return (&game->textures.we);
	}
	else
	{
		if (game->raycast.ray_dir_y > 0)
			return (&game->textures.so);
		else
			return (&game->textures.no);
	}
}

void	draw_column(t_game *game, int x)
{
	int		y;
	int		tex_y;
	int		color;
	t_img	*texture;

	texture = get_wall_texture(game);
	calculate_texture_coords(game, texture);
	y = 0;
	while (y < game->raycast.draw_start)
		img_pixel_put(&game->img, x, y++, game->textures.color_c);
	y = game->raycast.draw_start;
	while (y <= game->raycast.draw_end)
	{
		tex_y = (int)game->raycast.tex_pos % texture->height;
		game->raycast.tex_pos += game->raycast.step;
		color = get_texture_color(texture, game->raycast.tex_x, tex_y);
		if (game->raycast.side == 1)
			color = (color >> 1) & SHADOW_MASK;
		img_pixel_put(&game->img, x, y++, color);
	}
	y = game->raycast.draw_end + 1;
	while (y < WIN_H)
		img_pixel_put(&game->img, x, y++, game->textures.color_f);
}
