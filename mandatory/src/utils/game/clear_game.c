/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:07:37 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/22 19:39:51 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"
#include "mlx.h"
#include <stdlib.h>

/**
 * ENGLISH: Frees the memory allocated for the game, including textures, map,
 * 			 zbuffer, and MLX resources.
 *
 * SPANISH: Libera la memoria asignada para el juego, incluyendo texturas, mapa,
 * 			 zbuffer y recursos de MLX.
 *
 * @param game A pointer to the game structure to be cleared. / Un puntero a
 * 				la estructura del juego que se va a limpiar.
 */
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/**
 * ENGLISH: Frees the memory allocated for the textures in the game, including
 * 			 paths and MLX images.
 *
 * SPANISH: Libera la memoria asignada para las texturas en el juego, incluyendo
 * 			 rutas e imágenes de MLX.
 *
 * @param game A pointer to the game structure containing the textures to be
 * 			freed. / Un puntero a la estructura del juego que contiene las
 * 			texturas a liberar.
 */
static void	free_textures(t_game *game)
{
	if (!game)
		return ;
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_we)
		free(game->textures.path_we);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
	if (game->mlx_ptr && game->textures.no.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.no.img);
	if (game->mlx_ptr && game->textures.so.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.so.img);
	if (game->mlx_ptr && game->textures.we.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.we.img);
	if (game->mlx_ptr && game->textures.ea.img)
		mlx_destroy_image(game->mlx_ptr, game->textures.ea.img);
}

/**
 * ENGLISH: Clears the game by freeing all allocated resources, including
 * 			textures, map, zbuffer, and MLX resources.
 *
 * SPANISH: Limpia el juego liberando todos los recursos asignados, incluyendo
 * 			 texturas, mapa, zbuffer y recursos de MLX.
 *
 * @param game A pointer to the game structure to be cleared. / Un puntero a
 * 				la estructura del juego que se va a limpiar.
 */
void	clear_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx_ptr && game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	free_textures(game);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_map(game->map.grid);
	if (game->zbuffer)
		free(game->zbuffer);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}
