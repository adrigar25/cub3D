/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:46:06 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/01 22:26:10 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <math.h>

void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x;
	double	old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
}
