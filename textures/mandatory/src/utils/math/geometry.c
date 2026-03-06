/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:46:22 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/24 17:13:59 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

/**
 * ENGLISH: Returns the fractional part of a double (x - floor(x)).
 * 			example: fract(3.14) returns 0.14
 *
 * SPANISH: Devuelve la parte fraccionaria de un double (x - floor(x)).
 * 			ejemplo: fract(3.14) devuelve 0.14
 *
 * @param x The input value. / El valor de entrada.
 *
 * @return The fractional part of x. / La parte fraccionaria de x.
 */
double	fract(double x)
{
	return (x - floor(x));
}
