/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/16 13:42:07 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

typedef struct s_triangle
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		x3;
	int		y3;
}			t_triangle;

typedef struct s_minimap_dims
{
	int		px_center;
	int		py_center;
	int		target_w;
	int		target_h;
	int		start_x;
	int		start_y;
}			t_minimap_dims;

t_triangle	create_triangle(int x[3], int y[3]);
void		sort_triangle_vertices(t_triangle *tri);
void		fill_bottom_triangle(t_game *game, const t_triangle *tri);
void		fill_top_triangle(t_game *game, const t_triangle *tri);

#endif
