/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/07 18:06:36 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"
#include "minimap_bonus.h"

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

void	sort_triangle_vertices(t_triangle *tri)
{
	if (tri->y1 > tri->y2)
		swap_vertices(&tri->x1, &tri->y1, &tri->x2, &tri->y2);
	if (tri->y1 > tri->y3)
		swap_vertices(&tri->x1, &tri->y1, &tri->x3, &tri->y3);
	if (tri->y2 > tri->y3)
		swap_vertices(&tri->x2, &tri->y2, &tri->x3, &tri->y3);
}

t_triangle	create_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	t_triangle	tri;

	tri.x1 = x1;
	tri.y1 = y1;
	tri.x2 = x2;
	tri.y2 = y2;
	tri.x3 = x3;
	tri.y3 = y3;
	return (tri);
}
