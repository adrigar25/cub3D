/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/22 19:48:31 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "parse.h"
#include "render.h"
#include <stdlib.h>

/**
 * ENGLISH: Initializes the game data structure by allocating memory and setting
 * 			default values for textures and colors. It also allocates memory
 * 			for the zbuffer used in rendering.
 *
 * SPANISH: Inicializa la estructura de datos del juego asignando memoria y
 * 			estableciendo valores predeterminados para las texturas y colores.
 * 			También asigna memoria para el zbuffer utilizado en el renderizado.
 *
 * @return A pointer to the initialized game structure. / Un puntero a la
 * 			estructura del juego inicializada.
 */
t_game	*init_data(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_fprintf(2, RED "Error: Malloc failed\n" RESET);
		exit(EXIT_FAILURE);
	}
	game->textures.color_c = -1;
	game->textures.color_f = -1;
	game->zbuffer = malloc(sizeof(double) * WIN_W);
	if (!game->zbuffer)
	{
		free(game);
		ft_fprintf(2, RED "Error: Malloc failed (zbuffer)\n" RESET);
		exit(EXIT_FAILURE);
	}
	return (game);
}
