/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:05:09 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"

/**
 * ENGLISH: Iterates over every screen column, initialises the ray,
 *          runs the DDA algorithm, draws the resulting wall column,
 *          and stores the perpendicular distance in the z-buffer.
 *
 * SPANISH: Itera sobre cada columna de pantalla, inicializa el rayo,
 *          ejecuta el algoritmo DDA, dibuja la columna de pared resultante
 *          y almacena la distancia perpendicular en el z-buffer.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
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
		game->zbuffer[x] = game->raycast.perp_wall_dist;
		x++;
	}
}
