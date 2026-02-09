/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/09 17:12:10 by adriescr         ###   ########.fr       */
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
