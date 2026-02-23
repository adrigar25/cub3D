/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:29:01 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"

/**
 * ENGLISH: Initialises the ray direction and starting map cell for screen
 *          column x using the player position and camera plane.
 *
 * SPANISH: Inicializa la dirección del rayo y la celda de inicio en el
 *          mapa para la columna de pantalla x usando la posición del
 *          jugador y el plano de cámara.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Screen column index. / Índice de columna de pantalla.
 */
void	init_ray(t_game *game, int x)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
}
