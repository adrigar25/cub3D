/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_count_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:07:20 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "libft.h"
#include "sprite_bonus.h"

/**
 * ENGLISH: Returns 1 if the position (x, y) falls within the sprite
 *          scan window boundaries.
 *
 * SPANISH: Retorna 1 si la posición (x, y) está dentro de los límites
 *          de la ventana de escaneo de sprites.
 *
 * @param x X world coordinate. / Coordenada X en el mundo.
 * @param y Y world coordinate. / Coordenada Y en el mundo.
 * @param w Pointer to the sprite window. / Puntero a la ventana de sprites.
 *
 * @return 1 if inside, 0 if outside. / 1 si está dentro, 0 si fuera.
 */
static int	spr_is_in_window(double x, double y, const t_sprite_window *w)
{
	return (x >= (double)w->min_x && x <= (double)w->max_x
		&& y >= (double)w->min_y && y <= (double)w->max_y);
}

/**
 * ENGLISH: Counts visible map sprite tiles within the scan window that
 *          have a registered texture.
 *
 * SPANISH: Cuenta las casillas de sprite del mapa visibles dentro de la
 *          ventana de escaneo que tienen una textura registrada.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param w Sprite scan window. / Ventana de escaneo de sprites.
 *
 * @return Number of visible map sprites. / Número de sprites de mapa visibles.
 */
static int	spr_count_map(t_game *game, const t_sprite_window *w)
{
	int		count;
	int		y;
	int		x;
	char	tile;

	count = 0;
	y = w->min_y;
	while (y <= w->max_y && game->map.grid[y])
	{
		x = w->min_x;
		while (x <= w->max_x && game->map.grid[y][x])
		{
			tile = game->map.grid[y][x];
			if (!ft_strchr("X01NSEW", tile) && sprite_get_texture(game, tile))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/**
 * ENGLISH: Returns 1 if the enemy has at least one valid texture for its
 *          current animation state.
 *
 * SPANISH: Retorna 1 si el enemigo tiene al menos una textura válida para
 *          su estado de animación actual.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param e Pointer to the enemy. / Puntero al enemigo.
 *
 * @return 1 if texture available, 0 otherwise. /
 *         1 si hay textura disponible, 0 en caso contrario.
 */
static int	spr_has_enemy_texture(t_game *game, t_enemy *e)
{
	if (e->moving)
		return (game->e_txt_w1 != NULL || game->e_txt_w2 != NULL);
	return (game->e_txt_s != NULL);
}

/**
 * ENGLISH: Counts visible enemies within the scan window that have a
 *          valid texture for their current state.
 *
 * SPANISH: Cuenta los enemigos visibles dentro de la ventana de escaneo
 *          que tienen una textura válida para su estado actual.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param w Sprite scan window. / Ventana de escaneo de sprites.
 *
 * @return Number of visible enemy sprites. /
 *         Número de sprites de enemigo visibles.
 */
static int	spr_count_enemies(t_game *game, const t_sprite_window *w)
{
	int		count;
	t_enemy	*e;

	count = 0;
	e = game->enemies;
	while (e)
	{
		if (spr_is_in_window(e->x, e->y, w) && spr_has_enemy_texture(game, e))
			count++;
		e = e->next;
	}
	return (count);
}

/**
 * ENGLISH: Returns the total number of sprites (map + enemies) visible
 *          within the given scan window.
 *
 * SPANISH: Retorna el número total de sprites (mapa + enemigos) visibles
 *          dentro de la ventana de escaneo dada.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param w Sprite scan window. / Ventana de escaneo de sprites.
 *
 * @return Total visible sprite count. / Conteo total de sprites visibles.
 */
int	sprite_count_total_in_window(t_game *game, const t_sprite_window *w)
{
	return (spr_count_map(game, w) + spr_count_enemies(game, w));
}
