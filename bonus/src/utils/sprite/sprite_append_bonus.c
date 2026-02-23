/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_append_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:31 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "libft.h"
#include "sprite_bonus.h"

/**
 * ENGLISH: Computes the projection depth (transform Y) of a world-space
 *          sprite tile position relative to the player camera.
 *
 * SPANISH: Calcula la profundidad de proyección (transform Y) de la
 *          posición de una casilla de sprite en el espacio del mundo
 *          relativa a la cámara del jugador.
 *
 * @param p Pointer to the player structure. /
 *          Puntero a la estructura del jugador.
 * @param sx Sprite world X position. / Posición X del sprite en el mundo.
 * @param sy Sprite world Y position. / Posición Y del sprite en el mundo.
 *
 * @return Projection depth, or 0.0 if behind the camera. /
 *         Profundidad de proyección, o 0.0 si está detrás de la cámara.
 */
double	sprite_compute_depth(t_player *p, double sx, double sy)
{
	double	x;
	double	y;
	double	inv_det;
	double	transform_y;

	x = sx + 0.5 - p->pos_x;
	y = sy + 0.5 - p->pos_y;
	inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	transform_y = inv_det * (-p->plane_y * x + p->plane_x * y);
	if (transform_y > 0.05)
		return (transform_y);
	return (0.0);
}

/**
 * ENGLISH: Fills a t_draw_sprite entry with world position and depth.
 *
 * SPANISH: Rellena una entrada t_draw_sprite con la posición del mundo
 *          y la profundidad.
 *
 * @param new Pointer to the entry to fill. / Puntero a la entrada a rellenar.
 * @param x World X position. / Posición X en el mundo.
 * @param y World Y position. / Posición Y en el mundo.
 * @param depth Projection depth. / Profundidad de proyección.
 */
static void	add_sprite_info(t_draw_sprite *new, double x, double y,
		double depth)
{
	new->x = x;
	new->y = y;
	new->depth = depth;
}

/**
 * ENGLISH: Scans the sprite window for non-standard map tiles, looks up
 *          their texture and depth, and appends them to the draw list.
 *
 * SPANISH: Escanea la ventana de sprites en busca de casillas no
 *          estándar, busca su textura y profundidad y las añade a la
 *          lista de dibujo.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param w Sprite scan window. / Ventana de escaneo de sprites.
 * @param list Draw list to append to. / Lista de dibujo a la que añadir.
 * @param i Current index in the list. / Índice actual en la lista.
 *
 * @return Updated index after appending. / Índice actualizado tras añadir.
 */
int	sprite_append_map_sprites(t_game *game, const t_sprite_window *w,
		t_draw_sprite *list, int i)
{
	int			y;
	int			x;
	double		depth;
	t_texture	*tex;

	y = w->min_y - 1;
	while (++y <= w->max_y && game->map.grid[y])
	{
		x = w->min_x - 1;
		while (++x <= w->max_x && game->map.grid[y][x])
		{
			if (!ft_strchr("X01NSEWA", game->map.grid[y][x]))
			{
				tex = sprite_get_texture(game, game->map.grid[y][x]);
				depth = sprite_compute_depth(&game->player, x, y);
				if (tex && tex->img.img && depth > 0.0)
				{
					add_sprite_info(&list[i], x + 0.5, y + 0.5, depth);
					list[i++].tex = &tex->img;
				}
			}
		}
	}
	return (i);
}

/**
 * ENGLISH: Returns the correct animation texture for an enemy based on
 *          whether it is moving and which animation frame is active.
 *
 * SPANISH: Devuelve la textura de animación correcta para un enemigo
 *          según si se está moviendo y qué fotograma de animación está
 *          activo.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param e Pointer to the enemy. / Puntero al enemigo.
 *
 * @return Pointer to the matching texture. /
 *         Puntero a la textura correspondiente.
 */
static t_texture	*get_enemy_texture(t_game *game, t_enemy *e)
{
	if (e->moving)
	{
		if (e->anim_frame == 0)
			return (game->e_txt_w1);
		return (game->e_txt_w2);
	}
	return (game->e_txt_s);
}

/**
 * ENGLISH: Iterates over enemy list, checks visibility within the
 *          scan window, and appends each visible enemy to the draw list.
 *
 * SPANISH: Itera sobre la lista de enemigos, comprueba la visibilidad
 *          dentro de la ventana de escaneo y añade cada enemigo visible
 *          a la lista de dibujo.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param w Sprite scan window. / Ventana de escaneo de sprites.
 * @param list Draw list to append to. / Lista de dibujo a la que añadir.
 * @param i Current index in the list. / Índice actual en la lista.
 *
 * @return Updated index after appending. / Índice actualizado tras añadir.
 */
int	sprite_append_enemy_sprites(t_game *game, const t_sprite_window *w,
		t_draw_sprite *list, int i)
{
	t_enemy		*e;
	t_texture	*tex;
	double		depth;

	e = game->enemies;
	while (e)
	{
		if (e->x >= (double)w->min_x && e->x <= (double)w->max_x
			&& e->y >= (double)w->min_y && e->y <= (double)w->max_y)
		{
			tex = get_enemy_texture(game, e);
			depth = sprite_compute_depth(&game->player, e->x - 0.5, e->y - 0.5);
			if (tex && tex->img.img && depth > 0.0)
			{
				add_sprite_info(&list[i], e->x, e->y, depth);
				list[i].tex = &tex->img;
				i++;
			}
		}
		e = e->next;
	}
	return (i);
}
