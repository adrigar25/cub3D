/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_window_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 00:54:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 00:54:21 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sprite_helpers_bonus.h"

/*
	* ENGLISH: 	Compute the bounding box of tiles to
				check for sprites around the player.
	* SPANISH: 	Calcula el área de tiles a revisar
				para sprites alrededor del jugador.
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
	if (w->max_y >= game->map_h)
		w->max_y = game->map_h - 1;
	w->min_x = ptx - r;
	if (w->min_x < 0)
		w->min_x = 0;
	w->max_x = ptx + r;
	if (w->max_x >= game->map_w)
		w->max_x = game->map_w - 1;
}
