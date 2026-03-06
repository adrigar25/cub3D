/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:46:06 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

/**
 * ENGLISH: Rotates a 2D vector (*x, *y) by the given angle using a
 * 			rotation matrix.
 *
 * SPANISH: Rota un vector 2D (*x, *y) el ángulo dado usando una matriz
 * 			de rotación.
 *
 * @param x Pointer to the x component. / Puntero al componente x.
 * @param y Pointer to the y component. / Puntero al componente y.
 * @param angle Rotation angle in radians. / Ángulo de rotación en radianes.
 */
void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x;
	double	old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
}
