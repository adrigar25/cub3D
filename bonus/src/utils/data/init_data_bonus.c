/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 21:00:53 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "parse_bonus.h"
#include "player_bonus.h"
#include "render_bonus.h"
#include <stdlib.h>

static void	init_allowed_chars(t_game *game)
{
	const char	*default_allowed = " 01NSEWACX\n\t";
	int			i;

	i = 0;
	while (default_allowed[i])
	{
		game->allowed_chars[i] = default_allowed[i];
		i++;
	}
	game->allowed_count = i;
	game->allowed_chars[i] = '\0';
}

t_game	*init_data(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_fprintf(2, RED "Error: Malloc failed\n" RESET);
		exit(EXIT_FAILURE);
	}
	game->floor_color = -1;
	game->ceiling_color = -1;
	init_allowed_chars(game);
	game->zbuffer = malloc(sizeof(double) * WIN_W);
	if (!game->zbuffer)
	{
		free(game);
		ft_fprintf(2, RED "Error: Malloc failed (zbuffer)\n" RESET);
		exit(EXIT_FAILURE);
	}
	return (game);
}
