/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "raycast.h"
#include "render.h"

/**
 * ENGLISH: Calculates the texture coordinates (tex_x, tex_pos, step) for
 * 			the wall slice of the current column.
 *
 * SPANISH: Calcula las coordenadas de textura (tex_x, tex_pos, step) para
 * 			el segmento de pared de la columna actual.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 * @param texture Pointer to the wall texture image. / Puntero a la textura.
 */
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

/**
 * ENGLISH: Selects the correct wall texture based on which side and
 * 			direction the ray hit.
 *
 * SPANISH: Selecciona la textura de pared correcta según el lado y
 * 			la dirección en la que el rayo impacta.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 *
 * @return Pointer to the selected texture. /
 * 		Puntero a la textura seleccionada.
 */
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

/**
 * ENGLISH: Draws a full screen column: ceiling, textured wall slice and
 * 			floor pixels.
 *
 * SPANISH: Dibuja una columna completa de pantalla: techo, segmento de
 * 			pared texturizado y píxeles del suelo.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 * @param x The screen column to draw. / La columna de pantalla a dibujar.
 */
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
