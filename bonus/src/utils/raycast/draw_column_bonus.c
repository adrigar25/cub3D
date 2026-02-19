/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "game_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"

static void	calculate_text_coords(t_player p, t_raycast *ray, t_img *tex)
{
	if (ray->side == 0)
		ray->wall_x = p.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = p.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	ray->step = 1.0 * tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2
			- p.pitch) * ray->step;
}

static t_img	*get_wall_texture(t_game *game, char **map, t_raycast *raycast)
{
	t_texture	*txt;
	char		tile;

	tile = map[raycast->map_y][raycast->map_x];
	if (tile == 'D')
		txt = game->txt_door;
	else if (tile == 'A')
		txt = game->txt_exit;
	else if (raycast->side == 0)
	{
		txt = game->txt_we;
		if (raycast->ray_dir_x > 0)
			txt = game->txt_ea;
	}
	else
	{
		txt = game->txt_no;
		if (raycast->ray_dir_y > 0)
			txt = game->txt_so;
	}
	if (!txt || !txt->img.img)
		txt = game->txt_no;
	return (&txt->img);
}

static void	draw_ceiling_floor(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->raycast.draw_start)
		img_pixel_put(&game->img, x, y++, game->ceiling_color);
	y = game->raycast.draw_end + 1;
	while (y < WIN_H)
		img_pixel_put(&game->img, x, y++, game->floor_color);
}

static void	draw_textured_wall(t_game *game, int x, t_img *texture)
{
	int	y;
	int	tex_y;
	int	color;

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
}

void	draw_column(t_game *game, int x)
{
	t_img	*texture;

	texture = get_wall_texture(game, game->map.grid, &game->raycast);
	calculate_text_coords(game->player, &game->raycast, texture);
	if (game->raycast.draw_start < 0)
		game->raycast.tex_pos += game->raycast.step * -game->raycast.draw_start;
	if (game->raycast.draw_start < 0)
		game->raycast.draw_start = 0;
	if (game->raycast.draw_end >= WIN_H)
		game->raycast.draw_end = WIN_H - 1;
	draw_ceiling_floor(game, x);
	draw_textured_wall(game, x, texture);
}
