/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:48:36 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

/**
 * ENGLISH: Calculates the delta distance for a ray direction component.
 * 			Returns a very large value if the component is zero.
 *
 * SPANISH: Calcula la distancia delta para un componente de dirección del
 * 			rayo. Devuelve un valor muy grande si el componente es cero.
 *
 * @param ray_dir The ray direction component. / El componente de dirección.
 *
 * @return The delta distance value. / El valor de la distancia delta.
 */
double	calc_delta_dist(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	return (fabs(1.0 / ray_dir));
}

/**
 * ENGLISH: Returns the step direction (+1 or -1) based on the ray direction
 * 			component sign.
 *
 * SPANISH: Devuelve la dirección del paso (+1 o -1) según el signo del
 * 			componente de dirección del rayo.
 *
 * @param ray_dir The ray direction component. / El componente de dirección.
 *
 * @return 1 if ray_dir >= 0, or -1 if ray_dir < 0. /
 * 		1 si ray_dir >= 0, o -1 si ray_dir < 0.
 */
int	calc_step(double ray_dir)
{
	if (ray_dir < 0)
		return (-1);
	else
		return (1);
}

/**
 * ENGLISH: Calculates the distance from the player's position to the first
 * 			grid line intersection in the given direction.
 *
 * SPANISH: Calcula la distancia desde la posición del jugador hasta la
 * 			primera intersección con la cuadrícula en la dirección dada.
 *
 * @param pos Player coordinate on this axis. / Coordenada del jugador.
 * @param map Map cell index on this axis. / Índice de celda en el mapa.
 * @param ray_dir Ray direction component. / Componente de dirección.
 * @param delta_dist Delta distance value. / Valor de distancia delta.
 *
 * @return The initial side distance. / La distancia lateral inicial.
 */
double	calc_side_dist(double pos, int map, double ray_dir, double delta_dist)
{
	if (ray_dir < 0)
		return ((pos - map) * delta_dist);
	else
		return ((map + 1.0 - pos) * delta_dist);
}
