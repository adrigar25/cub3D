/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_window_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "sprite_bonus.h"

/**
 * ENGLISH: Computes the bounding box of map tiles to scan for sprites
 *          around the player, clamped to the map boundaries.
 *
 * SPANISH: Calcula el bounding box de casillas del mapa a escanear en
 *          busca de sprites alrededor del jugador, limitado a los bordes
 *          del mapa.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param w Output sprite window to fill. /
 *          Ventana de sprites de salida a rellenar.
 */
void	sprite_compute_scan_window(t_game *game, t_sprite_window *w)
{
	int	pty;
	int	ptx;
	int	r;

	pty = (int)game->player.pos_y;
	ptx = (int)game->player.pos_x;
	r = SPRITE_SCAN_RADIUS_TILES;
	w->min_y = pty - r;
	if (w->min_y < 0)
		w->min_y = 0;
	w->max_y = pty + r;
	if (w->max_y >= game->map.height)
		w->max_y = game->map.height - 1;
	w->min_x = ptx - r;
	if (w->min_x < 0)
		w->min_x = 0;
	w->max_x = ptx + r;
	if (w->max_x >= game->map.width)
		w->max_x = game->map.width - 1;
}
