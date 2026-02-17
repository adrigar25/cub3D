/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 22:30:49 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	valid_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len < extension_len)
		return (0);
	return (ft_strncmp(filename + filename_len - extension_len, extension,
			extension_len) == 0);
}

int	cub3d(char *file)
{
	t_game	*game_data;

	game_data = init_data();
	if (read_data(&game_data, file))
		return (clear_game(game_data, -1), 1);
	if (check_data(game_data))
		return (clear_game(game_data, -1), 1);
	if (check_map(game_data))
		return (clear_game(game_data, -1), 1);
	if (init_mlx(game_data))
		return (clear_game(game_data, -1), 1);
	if (load_images(game_data))
		return (clear_game(game_data, -1), 1);
	if (get_player_position(game_data))
		return (clear_game(game_data, -1), 1);
	start_game_loop(game_data);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_fprintf(2, "Usage: %s <map_file.cub>\n", argv[0]);
		return (-1);
	}
	if (!valid_extension(argv[1], ".cub"))
	{
		ft_fprintf(2, RED "Error: Map file must have a .cub extension\n" RESET);
		return (-1);
	}
	return (cub3d(argv[1]));
}
