/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:05:09 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "raycast.h"
#include "render.h"

/**
 * ENGLISH: Iterates over every screen column and performs raycasting to
 * 			render the 3D view.
 *
 * SPANISH: Itera sobre cada columna de pantalla y realiza el raycasting
 * 			para renderizar la vista 3D.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 */
void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, x);
		dda(game);
		draw_column(game, x);
		x++;
	}
}
