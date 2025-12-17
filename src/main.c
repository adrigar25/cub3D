/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 22:28:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free(game->texture_north);
	free(game->texture_south);
	free(game->texture_west);
	free(game->texture_east);
	free(game->color_floor);
	free(game->color_ceiling);
	free_map(game->map);
	free(game);
}

int	cub3d(char *file)
{
	t_game	*game_data;

	game_data = init_game(file);
	if (!game_data)
		return (handle_error("Game initialization failed"));
	if (check_map(game_data->map) == -1)
	{
		free_game(game_data);
		return (handle_error("Map validation failed"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv || !argv[0])
		return (handle_error("Invalid arguments"));
	return (cub3d(argv[1]));
}