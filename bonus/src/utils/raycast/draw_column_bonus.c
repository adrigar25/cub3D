/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "game_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"

/**
 * ENGLISH: Computes the wall X texture coordinate and texture step for
 *          the current ray hit, accounting for ray direction to avoid
 *          texture mirroring.
 *
 * SPANISH: Calcula la coordenada X de textura de la pared y el paso de
 *          textura para el impacto del rayo actual, teniendo en cuenta la
 *          dirección del rayo para evitar el espejado de texturas.
 *
 * @param p Player structure. / Estructura del jugador.
 * @param ray Pointer to the raycast data. / Puntero a los datos del rayo.
 * @param tex Pointer to the wall texture image. /
 *            Puntero a la imagen de textura de la pared.
 */
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

/**
 * ENGLISH: Returns the appropriate texture for the hit wall tile,
 *          selecting by tile type (door/exit) or ray side (N/S/E/W).
 *
 * SPANISH: Retorna la textura apropiada para la casilla de pared
 *          impactada, seleccionando por tipo de casilla (puerta/salida)
 *          o lado del rayo (N/S/E/O).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param map The map grid. / La cuadrícula del mapa.
 * @param raycast Pointer to the raycast data. /
 *                Puntero a los datos del rayo.
 *
 * @return Pointer to the selected texture image. /
 *         Puntero a la imagen de textura seleccionada.
 */
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

/**
 * ENGLISH: Fills the ceiling (top) and floor (bottom) pixel columns with
 *          their respective flat colours for screen column x.
 *
 * SPANISH: Rellena las columnas de píxeles del techo (arriba) y suelo
 *          (abajo) con sus colores planos respectivos para la columna x.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Screen column index. / Índice de columna de pantalla.
 */
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

/**
 * ENGLISH: Draws the textured wall slice for screen column x, applying
 *          a darkness tint to east/west (side==1) faces.
 *
 * SPANISH: Dibuja la franja de pared texturizada para la columna x de
 *          pantalla, aplicando una oscuridad a las caras este/oeste.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Screen column index. / Índice de columna de pantalla.
 * @param texture Pointer to the selected wall texture. /
 *                Puntero a la textura de pared seleccionada.
 */
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

/**
 * ENGLISH: Orchestrates drawing of screen column x: selects texture,
 *          calculates coords, clamps draw bounds, then draws ceiling,
 *          floor and textured wall.
 *
 * SPANISH: Orquesta el dibujado de la columna x de pantalla: selecciona
 *          textura, calcula coordenadas, limita los límites de dibujo,
 *          luego dibuja techo, suelo y pared texturizada.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Screen column index. / Índice de columna de pantalla.
 */
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
