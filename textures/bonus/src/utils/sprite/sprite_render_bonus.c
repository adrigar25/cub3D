/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "sprite_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Comparator for qsort: sorts sprites by depth descending so
 *          that distant sprites are drawn first (painter's algorithm).
 *
 * SPANISH: Comparador para qsort: ordena sprites por profundidad
 *          descendente para que los más lejanos se dibujen primero
 *          (algoritmo del pintor).
 *
 * @param a Pointer to first t_draw_sprite. / Puntero al primer t_draw_sprite.
 * @param b Pointer to second t_draw_sprite. /
 *          Puntero al segundo t_draw_sprite.
 *
 * @return Positive if a is closer, negative if b is closer. /
 *         Positivo si a es más cercano, negativo si lo es b.
 */
static int	spr_cmp_by_depth(const void *a, const void *b)
{
	const t_draw_sprite	*sa;
	const t_draw_sprite	*sb;

	sa = (const t_draw_sprite *)a;
	sb = (const t_draw_sprite *)b;
	if (sa->depth < sb->depth)
		return (1);
	if (sa->depth > sb->depth)
		return (-1);
	return (0);
}

/**
 * ENGLISH: Sorts the sprite list by depth and draws each one in order.
 *
 * SPANISH: Ordena la lista de sprites por profundidad y dibuja cada uno
 *          en orden.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param list Array of drawable sprites. / Array de sprites a dibujar.
 * @param count Number of sprites in the array. /
 *              Número de sprites en el array.
 */
static void	spr_render_sorted(t_game *game, t_draw_sprite *list, int count)
{
	int	i;

	qsort(list, count, sizeof(t_draw_sprite), spr_cmp_by_depth);
	i = 0;
	while (i < count)
	{
		sprite_draw_at(game, list[i].tex, list[i].x, list[i].y);
		i++;
	}
}

/**
 * ENGLISH: Main sprite render function. Counts visible sprites, allocates
 *          a draw list, fills it with map and enemy sprites, sorts by
 *          depth, and draws them all.
 *
 * SPANISH: Función principal de renderizado de sprites. Cuenta los sprites
 *          visibles, reserva una lista de dibujo, la rellena con sprites
 *          del mapa y enemigos, los ordena por profundidad y los dibuja.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	sprite_render(t_game *game)
{
	int				count;
	t_draw_sprite	*list;
	int				i;
	t_sprite_window	window;

	if (!game || !game->map.grid)
		return ;
	sprite_compute_scan_window(game, &window);
	count = sprite_count_total_in_window(game, &window);
	if (count <= 0)
		return ;
	list = (t_draw_sprite *)malloc(sizeof(t_draw_sprite) * count);
	if (!list)
		return ;
	i = sprite_append_map_sprites(game, &window, list, 0);
	i = sprite_append_enemy_sprites(game, &window, list, i);
	if (i > 0)
		spr_render_sorted(game, list, i);
	free(list);
}
