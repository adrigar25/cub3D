/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:47:14 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "player.h"

/**
 * ENGLISH: Returns 1 if the given map coordinates are outside the valid
 * 			map bounds.
 *
 * SPANISH: Devuelve 1 si las coordenadas dadas están fuera de los límites
 * 			válidos del mapa.
 *
 * @param map_x Map column index. / Índice de columna del mapa.
 * @param map_y Map row index. / Índice de fila del mapa.
 * @param map The NULL-terminated map array. / El array del mapa.
 *
 * @return 1 if out of bounds, 0 if within bounds. /
 * 		1 si está fuera de límites, 0 si está dentro.
 */
int	is_out_of_bounds(int map_x, int map_y, char **map)
{
	if (map_y < 0 || map_x < 0)
		return (1);
	if (!map[map_y] || !map[map_y][map_x])
		return (1);
	return (0);
}

/**
 * ENGLISH: Calculates the exact point where the ray hits the wall surface,
 * 			used for texture mapping.
 *
 * SPANISH: Calcula el punto exacto donde el rayo impacta la superficie de
 * 			la pared, usado para el mapeo de texturas.
 *
 * @param player The player structure. / La estructura del jugador.
 * @param ray The raycast structure. / La estructura del rayo.
 *
 * @return The wall impact coordinate. / La coordenada de impacto en la pared.
 */
double	calc_wall_impact(t_player player, t_raycast ray)
{
	if (ray.side == 0)
		return (player.pos_y + ray.perp_wall_dist * ray.ray_dir_y);
	else
		return (player.pos_x + ray.perp_wall_dist * ray.ray_dir_x);
}

/**
 * ENGLISH: Converts a fractional wall hit position to a texture x coordinate,
 * 			correcting the orientation based on ray direction.
 *
 * SPANISH: Convierte la posición fraccional de impacto en la pared a una
 * 			coordenada x de textura, corrigiendo la orientación según el rayo.
 *
 * @param wall_x Fractional wall hit position. / Posición fraccional.
 * @param side Side hit (0 = x-axis, 1 = y-axis). / Lado impactado.
 * @param ray_dir Ray direction component. / Componente de dirección.
 * @param tex_width Texture width in pixels. / Ancho de la textura.
 *
 * @return The texture x coordinate. / La coordenada x de la textura.
 */
double	calc_texture_x_coord(double wall_x, int side, double ray_dir,
		int tex_width)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex_width);
	if (side == 0 && ray_dir > 0)
		tex_x = tex_width - tex_x - 1;
	if (side == 1 && ray_dir < 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}
