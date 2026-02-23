/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "minimap_bonus.h"

/**
 * ENGLISH: Swaps two (x, y) vertex pairs in a triangle.
 *
 * SPANISH: Intercambia dos pares de vértices (x, y) en un triángulo.
 *
 * @param a Pointer to the first x component. / Puntero al primer x.
 * @param b Pointer to the first y component. / Puntero al primer y.
 * @param c Pointer to the second x component. / Puntero al segundo x.
 * @param d Pointer to the second y component. / Puntero al segundo y.
 */
static void	swap_vertices(int *a, int *b, int *c, int *d)
{
	int	tmp_a;
	int	tmp_b;

	tmp_a = *a;
	*a = *c;
	*c = tmp_a;
	tmp_b = *b;
	*b = *d;
	*d = tmp_b;
}

/**
 * ENGLISH: Sorts the three triangle vertices by ascending Y so that
 *          y1 <= y2 <= y3, as required by the scanline fill functions.
 *
 * SPANISH: Ordena los tres vértices del triángulo por Y ascendente de
 *          modo que y1 <= y2 <= y3, según requieren las funciones de
 *          relleno por escaneado.
 *
 * @param tri Pointer to the triangle to sort. /
 *            Puntero al triángulo a ordenar.
 */
void	sort_triangle_vertices(t_triangle *tri)
{
	if (tri->y1 > tri->y2)
		swap_vertices(&tri->x1, &tri->y1, &tri->x2, &tri->y2);
	if (tri->y1 > tri->y3)
		swap_vertices(&tri->x1, &tri->y1, &tri->x3, &tri->y3);
	if (tri->y2 > tri->y3)
		swap_vertices(&tri->x2, &tri->y2, &tri->x3, &tri->y3);
}

/**
 * ENGLISH: Creates and returns a t_triangle from two arrays of three
 *          integer X and Y coordinates.
 *
 * SPANISH: Crea y devuelve un t_triangle a partir de dos arrays de tres
 *          coordenadas enteras X e Y.
 *
 * @param x Array of three X coordinates. /
 *           Array de tres coordenadas X.
 * @param y Array of three Y coordinates. /
 *           Array de tres coordenadas Y.
 *
 * @return A populated t_triangle structure. /
 *         Una estructura t_triangle rellena.
 */
t_triangle	create_triangle(int x[3], int y[3])
{
	t_triangle	tri;

	tri.x1 = x[0];
	tri.y1 = y[0];
	tri.x2 = x[1];
	tri.y2 = y[1];
	tri.x3 = x[2];
	tri.y3 = y[2];
	return (tri);
}
