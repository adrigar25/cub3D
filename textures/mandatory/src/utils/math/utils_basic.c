/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:39:09 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/24 17:14:48 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

/**
 * ENGLISH: Divides num by denom, returning def if denom is zero.
 *
 * SPANISH: Divide num entre denom, devolviendo def si denom es cero.
 *
 * @param num Numerator. / Numerador.
 * @param denom Denominator. / Denominador.
 * @param def Default value if denom is zero. / Valor por defecto.
 *
 * @return num / denom, or def if denom == 0. /
 * 		num / denom, o def si denom == 0.
 */
double	safe_div(double num, double denom, double def)
{
	if (denom == 0.0)
		return (def);
	return (num / denom);
}

/**
 * ENGLISH: Clamps a value between min and max (inclusive).
 * 			example: 	clamp(5, 1, 10) returns 5,
 * 						clamp(-1, 0, 10) returns 0,
 * 						clamp(15, 0, 10) returns 10.
 *
 * SPANISH: Limita un valor entre min y max (ambos incluidos).
 * 			ejemplo: 	clamp(5, 1, 10) devuelve 5,
 * 						clamp(-1, 0, 10) devuelve 0,
 * 						clamp(15, 0, 10) devuelve 10.
 *
 * @param val The value to clamp. / El valor a limitar.
 * @param min The minimum boundary. / El límite mínimo.
 * @param max The maximum boundary. / El límite máximo.
 *
 * @return The clamped value. / El valor limitado.
 */
double	clamp(double val, double min, double max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

/**
 * ENGLISH: Returns the absolute value of a double.
 *
 * SPANISH: Devuelve el valor absoluto de un double.
 *
 * @param x The value to compute the absolute of. / El valor.
 *
 * @return The absolute value of x. / El valor absoluto de x.
 */
double	fabs_custom(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}
