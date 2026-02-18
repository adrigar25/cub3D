/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:06:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "parse.h"
#include "render.h"
#include <stdlib.h>

t_game	*init_data(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_fprintf(2, RED "Error: Malloc failed\n" RESET);
		exit(EXIT_FAILURE);
	}
	game->textures.color_c = -1;
	game->textures.color_f = -1;
	game->textures.no.img = NULL;
	game->textures.so.img = NULL;
	game->textures.we.img = NULL;
	game->textures.ea.img = NULL;
	game->textures.path_no = NULL;
	game->textures.path_so = NULL;
	game->textures.path_we = NULL;
	game->textures.path_ea = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->zbuffer = malloc(sizeof(double) * WIN_W);
	if (!game->zbuffer)
	{
		free(game);
		ft_fprintf(2, RED "Error: Malloc failed (zbuffer)\n" RESET);
		exit(EXIT_FAILURE);
	}
	return (game);
}
