/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:39:09 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:10:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

double	safe_div(double num, double denom, double def)
{
	if (denom == 0.0)
		return (def);
	return (num / denom);
}

double	clamp(double val, double min, double max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

double	fabs_custom(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}
