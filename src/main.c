/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 18:31:48 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d(char *file)
{
	t_game	*game_data;

	game_data = malloc(sizeof(t_game));
	if (!game_data)
		return (ft_error("cub3d", (char *[]){"Memory allocation failed", NULL}),
			-1);
	if (init_mlx(game_data) == -1)
		return (clear_game(game_data), -1);
	read_data(&game_data, file);
	if (!game_data)
		return (ft_error("cub3d", (char *[]){"Failed to read game data", NULL}),
			-1);
	if (check_map(game_data->map) == -1)
		return (clear_game(game_data), -1);
	get_player_position(game_data);
	start_game_loop(game_data);
	clear_game(game_data);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv || !argv[0])
		return (ft_error("main", (char *[]){"Usage: ./cub3D <map_file.cub>",
				NULL}), -1);
	return (cub3d(argv[1]));
}
