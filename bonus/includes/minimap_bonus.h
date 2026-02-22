/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/22 17:44:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 00:00:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== MINIMAP CONFIGURATION ========== */
# ifndef MINIMAP_H
#  define MINIMAP_H 200
# endif
# ifndef MINIMAP_W
#  define MINIMAP_W 200
# endif
# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE 30
# endif
# ifndef MINIMAP_BORDER
#  define MINIMAP_BORDER 2
# endif
# ifndef MINIMAP_PLAYER_SIZE
#  define MINIMAP_PLAYER_SIZE 5
# endif
# ifndef MINIMAP_PLAYER_COLOR
#  define MINIMAP_PLAYER_COLOR 0x0000FF
# endif
# ifndef MINIMAP_WALL_COLOR
#  define MINIMAP_WALL_COLOR 0x666666
# endif
# ifndef MINIMAP_FLOOR_COLOR
#  define MINIMAP_FLOOR_COLOR 0x9c9c9c
# endif
# ifndef MINIMAP_DOOR_COLOR
#  define MINIMAP_DOOR_COLOR 0x8B4513
# endif
# ifndef MINIMAP_EXIT_COLOR
#  define MINIMAP_EXIT_COLOR 0x00CC44
# endif
# ifndef MINIMAP_BORDER_COLOR
#  define MINIMAP_BORDER_COLOR 0xFFFFFF
# endif

/* ========== TRIANGLE HELPERS ========== */
typedef struct s_triangle
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
	int					x3;
	int					y3;
}						t_triangle;

typedef struct s_minimap_dims
{
	int					px_center;
	int					py_center;
	int					target_w;
	int					target_h;
	int					start_x;
	int					start_y;
}						t_minimap_dims;

t_triangle				create_triangle(int x[3], int y[3]);
void					sort_triangle_vertices(t_triangle *tri);
void					fill_bottom_triangle(t_game *game,
							const t_triangle *tri);
void					fill_top_triangle(t_game *game, const t_triangle *tri);

/* ========== MINIMAP UTILITIES ========== */
void					draw_player(t_game *game, double center_x,
							double center_y);
int						render_minimap(t_game *game);
int						has_floor_nearby(t_game *game, int x, int y);
void					put_minimap_tile(t_game *game, int px, int py,
							t_fcoord world);
void					clear_map(t_game *game);

#endif /* MINIMAP_BONUS_H */
