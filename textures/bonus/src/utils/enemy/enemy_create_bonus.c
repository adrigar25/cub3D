/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_create_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "enemy_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Sets the tile coordinates and floating-point position of an
 *          enemy, centred within its tile.
 *
 * SPANISH: Establece las coordenadas de casilla y posición de punto
 *          flotante del enemigo, centrado dentro de su casilla.
 *
 * @param e Pointer to the enemy. / Puntero al enemigo.
 * @param tile_x Tile column index. / Índice de columna de la casilla.
 * @param tile_y Tile row index. / Índice de fila de la casilla.
 */
static void	set_enemy_coords(t_enemy *e, int tile_x, int tile_y)
{
	e->tile_x = tile_x;
	e->tile_y = tile_y;
	e->x = (float)tile_x + 0.5f;
	e->y = (float)tile_y + 0.5f;
}

/**
 * ENGLISH: Allocates and initialises a new enemy at the given map tile.
 *
 * SPANISH: Reserva e inicializa un nuevo enemigo en la casilla de mapa
 *          indicada.
 *
 * @param tile_x Tile column index. / Índice de columna de la casilla.
 * @param tile_y Tile row index. / Índice de fila de la casilla.
 *
 * @return Pointer to the new enemy, or NULL on allocation failure. /
 *         Puntero al nuevo enemigo, o NULL si falla la reserva.
 */
t_enemy	*create_enemy(int tile_x, int tile_y)
{
	t_enemy	*e;

	e = (t_enemy *)malloc(sizeof(t_enemy));
	if (!e)
		return (NULL);
	e->next = NULL;
	set_enemy_coords(e, tile_x, tile_y);
	e->last_x = e->x;
	e->last_y = e->y;
	e->moving = 0;
	e->anim_frame = 0;
	e->anim_timer = 0;
	return (e);
}
