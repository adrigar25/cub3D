/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:46:22 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

/**
 * ENGLISH: Returns the fractional part of a double (x - floor(x)).
 *
 * SPANISH: Devuelve la parte fraccionaria de un double (x - floor(x)).
 *
 * @param x The input value. / El valor de entrada.
 *
 * @return The fractional part of x. / La parte fraccionaria de x.
 */
double	fract(double x)
{
	return (x - floor(x));
}
