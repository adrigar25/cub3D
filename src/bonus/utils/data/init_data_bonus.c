/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/29 23:43:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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
	game->textures.door.img = NULL;
	game->textures.path_no = NULL;
	game->textures.path_so = NULL;
	game->textures.path_we = NULL;
	game->textures.path_ea = NULL;
	game->textures.path_door = NULL;
	game->map = NULL;
	game->network = NULL;
	return (game);
}
