/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/19 12:43:41 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_draw_start(int line_height)
{
	int	draw_start;

	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

int	ft_draw_end(int line_height)
{
	int	draw_end;

	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	return (draw_end);
}

static void	calculate_texture_coords(t_game *game, t_img *texture)
{
	// Calcular donde exactamente se golpeó la pared
	if (game->raycast.side == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.perp_wall_dist
			* game->raycast.ray_dir_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.perp_wall_dist
			* game->raycast.ray_dir_x;
	game->raycast.wall_x -= floor(game->raycast.wall_x);
	// Calcular x coordinate en la textura
	game->raycast.tex_x = (int)(game->raycast.wall_x * (double)texture->width);
	if (game->raycast.side == 0 && game->raycast.ray_dir_x > 0)
		game->raycast.tex_x = texture->width - game->raycast.tex_x - 1;
	if (game->raycast.side == 1 && game->raycast.ray_dir_y < 0)
		game->raycast.tex_x = texture->width - game->raycast.tex_x - 1;
	// Calcular step y tex_pos para mapping vertical
	game->raycast.step = 1.0 * texture->height / game->raycast.line_height;
	game->raycast.tex_pos = (game->raycast.draw_start - WINDOW_HEIGHT / 2
			+ game->raycast.line_height / 2) * game->raycast.step;
}

static t_img	*get_wall_texture(t_game *game)
{
	if (game->raycast.side == 0) // Paredes verticales (norte/sur)
	{
		if (game->raycast.ray_dir_x > 0)
			return (&game->textures.ea); // Este
		else
			return (&game->textures.we); // Oeste
	}
	else // Paredes horizontales (este/oeste)
	{
		if (game->raycast.ray_dir_y > 0)
			return (&game->textures.so); // Sur
		else
			return (&game->textures.no); // Norte
	}
}

void	draw_column(t_game *game, int x)
{
	int		y;
	int		tex_y;
	int		color;
	t_img	*texture;

	game->raycast.draw_start = ft_draw_start(game->raycast.line_height);
	game->raycast.draw_end = ft_draw_end(game->raycast.line_height);
	texture = get_wall_texture(game);
	calculate_texture_coords(game, texture); // Dibujar techo (negro)
	y = 0;
	while (y < game->raycast.draw_start)
	{
		img_pixel_put(&game->img, x, y, game->textures.color_ceiling);
		y++;
	}
	// Dibujar pared con textura
	y = game->raycast.draw_start;
	while (y <= game->raycast.draw_end)
	{
		tex_y = (int)game->raycast.tex_pos % texture->height;
		game->raycast.tex_pos += game->raycast.step;
		color = get_texture_color(texture, game->raycast.tex_x, tex_y);
		// Aplicar sombreado para paredes horizontales
		if (game->raycast.side == 1)
			color = (color >> 1) & 8355711; // Dividir RGB entre 2
		img_pixel_put(&game->img, x, y, color);
		y++;
	} // Dibujar suelo (gris oscuro)
	y = game->raycast.draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		img_pixel_put(&game->img, x, y, game->textures.color_floor);
		y++;
	}
}
