/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:29:01 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "raycast.h"
#include "render.h"

/**
 * ENGLISH: Initializes the ray direction and map position for column x.
 *
 * SPANISH: Inicializa la dirección del rayo y la posición en el mapa para
 * 			la columna x.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 * @param x The screen column index. / El índice de columna en pantalla.
 */
void	init_ray(t_game *game, int x)
{
	t_raycast	*ray;

	ray = &game->raycast;
	ray->camera_x = camera_x(x, WIN_W);
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
}
