/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/19 13:46:06 by agarcia          ###   ########.fr       */
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
	if (init_mlx(game_data) || read_data(&game_data, file) == -1
		|| check_map(game_data->map) == -1)
		return (clear_game(game_data), -1);
	get_player_position(game_data);
	start_game_loop(game_data);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv || !argv[0] || ft_strncmp(argv[1]
			+ ft_strlen(argv[1]) - 4, ".cub", 4))
		return (ft_error("main", (char *[]){"Usage: ./cub3D <map_file.cub>",
				NULL}), -1);
	return (cub3d(argv[1]));
}
