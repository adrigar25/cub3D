/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_put_image_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/03 00:08:51 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

// Dibuja la imagen "image" centrada en la celda del mapa (map_x, map_y)
// dentro del buffer del minimapa, respetando el radio y borde del minimapa.
void	minimap_put_image_at(t_game *game, t_img *image, int map_x, int map_y)
{
	double	center_x;
	double	center_y;
	double	tile_size;
	double	s;
	double	target_cx;
	double	target_cy;
	double	dx;
	double	dy;
	double	rel_x;
	double	rel_y;
	int		px_center;
	int		py_center;
	int		start_x;
	int		start_y;
	double	radius;
	int		ix;
	int		iy;
	int		tx;
	int		ty;
	double	distance;
	int		color;
	int		target_w;
	int		target_h;
	int		src_x;
	int		src_y;
	char	*src;

	if (!game || !image || !image->img)
		return ;
	center_x = game->minimap.width / 2.0;
	center_y = game->minimap.height / 2.0;
	tile_size = MINIMAP_SCALE;
	s = tile_size / 2.0;
	// Centro de la celda objetivo en coordenadas de mapa
	target_cx = (double)map_x + 0.5;
	target_cy = (double)map_y + 0.5;
	// Vector desde el jugador al objetivo
	dx = target_cx - game->player.pos_x;
	dy = target_cy - game->player.pos_y;
	// Convertir vector del mundo a desplazamiento de píxeles en el minimapa
	rel_x = s * (dx * game->player.dir_y - dy * game->player.dir_x);
	rel_y = -s * (dx * game->player.dir_x + dy * game->player.dir_y);
	px_center = (int)(center_x + rel_x);
	py_center = (int)(center_y + rel_y);
	// Tamaño objetivo basado en la escala del minimapa (media baldosa)
	target_w = (int)(MINIMAP_SCALE / 2.0);
	if (target_w > image->width)
		target_w = image->width;
	target_h = (int)((double)image->height * (double)target_w
			/ (double)image->width);
	if (target_h < 1)
		target_h = 1;
	start_x = px_center - target_w / 2;
	start_y = py_center - target_h / 2;
	radius = center_x;
	for (iy = 0; iy < target_h; iy++)
	{
		ty = start_y + iy;
		if (ty < 0 || ty >= game->minimap.height)
			continue ;
		for (ix = 0; ix < target_w; ix++)
		{
			tx = start_x + ix;
			if (tx < 0 || tx >= game->minimap.width)
				continue ;
			distance = sqrt((tx - center_x) * (tx - center_x) + (ty - center_y)
					* (ty - center_y));
			if (distance > radius - MINIMAP_BORDER)
				continue ;
			// Mapear pixel destino a origen (nearest-neighbor)
			src_x = (int)((double)ix * (double)image->width / (double)target_w);
			src_y = (int)((double)iy * (double)image->height
					/ (double)target_h);
			// Leer RGBA directamente respetando endian para alpha correcto
			{
				unsigned char a, r, g, b;
				src = image->addr + (src_y * image->line_len + src_x
						* (image->bpp / 8));
				if (image->endian)
				{
					// Big endian: [A,R,G,B]
					a = (unsigned char)src[0];
					r = (unsigned char)src[1];
					g = (unsigned char)src[2];
					b = (unsigned char)src[3];
				}
				else
				{
					// Little endian (macOS MLX típico): [B,G,R,A]
					b = (unsigned char)src[0];
					g = (unsigned char)src[1];
					r = (unsigned char)src[2];
					a = (unsigned char)src[3];
				}
				if (a == 0)
					continue ;
				color = ((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;
				img_pixel_put(&game->minimap, tx, ty, color);
			}
		}
	}
}
