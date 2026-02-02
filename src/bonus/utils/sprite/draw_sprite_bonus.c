/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:58:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 23:59:20 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

// Distancia mínima (en espacio de cámara) para dibujar el sprite
#ifndef SPRITE_NEAR_CLIP
# define SPRITE_NEAR_CLIP 0.05
#endif


static int	is_transparent_color(t_img *texture, int color)
{
	int	key;

	// Usa el color del píxel (0,0) del sprite como clave de transparencia.
	// Funciona para XPM sin canal alpha con fondo uniforme.
	if (!texture || !texture->addr)
		return (0);
	key = *(unsigned int *)texture->addr; // color en (0,0)
	return (color == key);
}

void	draw_sprite_at(t_game *game, t_img *texture, double world_x,
		double world_y, double size)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	double	rel_x;
	int		tex_y;
	double	rel_y;
	int		color;

	// Vector del sprite relativo al jugador
	sprite_x = world_x - game->player.pos_x;
	sprite_y = world_y - game->player.pos_y;
	// Si estamos demasiado cerca en el mundo (mismo tile o muy próximo),
	// Matriz de transformación inversa (proyección a espacio de cámara)
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite_x - game->player.dir_x
			* sprite_y);
	transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	// Si está demasiado cerca o detrás de la cámara, no dibujar
	if (transform_y <= SPRITE_NEAR_CLIP)
		return ;
	// Coordenada X en pantalla
	screen_x = (int)((WIN_W / 2.0) * (1 + transform_x / transform_y));
	// Escalado por distancia (más lejos => más pequeño)
	if (size <= 0)
		size = 1.0;
	sprite_height = (int)fabs((WIN_H / transform_y) * size);
	// Mantener la proporción de la textura para el ancho
	if (texture->height > 0)
		sprite_width = (int)((double)sprite_height * (double)texture->width
				/ (double)texture->height);
	else
		sprite_width = sprite_height;
	// Evitar tamaños degenerados
	if (sprite_height < 1)
		sprite_height = 1;
	if (sprite_width < 1)
		sprite_width = 1;
	// Límites verticales (aplicando pitch del jugador)
	// Guardamos el inicio y fin originales para recorte correcto (sin reescalar)
	{
		double y0 = -sprite_height / 2.0 + WIN_H / 2.0 + game->player.pitch;
		double y1 =  sprite_height / 2.0 + WIN_H / 2.0 + game->player.pitch;
		draw_start_y = (int)y0;
		draw_end_y = (int)y1;
		if (draw_start_y < 0)
			draw_start_y = 0;
		if (draw_end_y >= WIN_H)
			draw_end_y = WIN_H - 1;
		// Reutilizamos y0 para mapear y->tex_y sin comprimir el sprite visible
		// Guardamos y0 en rel_y como base para el cálculo de textura
		rel_y = y0; // nota: rel_y se usa como base y0
	}
	// Límites horizontales
	draw_start_x = -sprite_width / 2 + screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + screen_x;
	if (draw_end_x >= WIN_W)
		draw_end_x = WIN_W - 1;
	stripe = draw_start_x;
	while (stripe <= draw_end_x)
	{
		// Profundidad frente a paredes: usar zbuffer por columna
		if (transform_y >= game->zbuffer[stripe])
		{
			stripe++;
			continue ;
		}
		rel_x = (double)(stripe - (-sprite_width / 2 + screen_x));
		tex_x = (int)(rel_x * texture->width / (double)sprite_width);
		if (tex_x < 0 || tex_x >= texture->width)
		{
			stripe++;
			continue ;
		}
		for (int y = draw_start_y; y <= draw_end_y; ++y)
		{
			// Mapear posición de pantalla a coordenada de textura respecto al inicio original y0
			tex_y = (int)(((double)y - rel_y) * (double)texture->height / (double)sprite_height);
			if (tex_y < 0 || tex_y >= texture->height)
				continue ;
			color = get_texture_color(texture, tex_x, tex_y);
			if (!is_transparent_color(texture, color))
				img_pixel_put(&game->img, stripe, y, color);
		}
		stripe++;
	}
}
