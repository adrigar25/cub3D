/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/30 00:29:33 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static void	calculate_texture_coords(t_game *game, t_img *texture)
{
	if (game->raycast.side == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.perp_wall_dist
			* game->raycast.ray_dir_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.perp_wall_dist
			* game->raycast.ray_dir_x;
	game->raycast.wall_x -= floor(game->raycast.wall_x);
	game->raycast.tex_x = (int)(game->raycast.wall_x * (double)texture->width);
	if (game->raycast.side == 0 && game->raycast.ray_dir_x > 0)
		game->raycast.tex_x = texture->width - game->raycast.tex_x - 1;
	if (game->raycast.side == 1 && game->raycast.ray_dir_y < 0)
		game->raycast.tex_x = texture->width - game->raycast.tex_x - 1;
	game->raycast.step = 1.0 * texture->height / game->raycast.line_height;
	game->raycast.tex_pos = (game->raycast.draw_start - WIN_H / 2
			+ game->raycast.line_height / 2 - game->player.pitch)
		* game->raycast.step;
}

static t_img	*get_wall_texture(t_game *game)
{
	if (game->map[game->raycast.map_y][game->raycast.map_x] == 'D')
		return (&game->textures.door);
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
	if (game->raycast.draw_start < 0)
		game->raycast.tex_pos += game->raycast.step * -game->raycast.draw_start;
	if (game->raycast.draw_start < 0)
		game->raycast.draw_start = 0;
	if (game->raycast.draw_end >= WIN_H)
		game->raycast.draw_end = WIN_H - 1;
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
