/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 17:44:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	get_data(t_game *game_data, int fd)
{
	char	*line;
	int		lastLine;

	lastLine = 0;
	line = ft_get_next_line(fd);
	while (line)
	{
		lastLine = (line[ft_strlen(line) - 1] == '\n');
		if (ft_strncmp(line, "NO ", 3) == 0)
			game_data->textures->no_txtr = mlx_png_file_to_image(ft_substr(line,
						3, ft_strlen(line) - 3 - lastLine));
		else if (ft_strncmp(line, "SO ", 3) == 0)
			game_data->textures->so_txtr = mlx_png_file_to_image(ft_substr(line,
						3, ft_strlen(line) - 3 - lastLine));
		else if (ft_strncmp(line, "WE ", 3) == 0)
			game_data->textures->we_txtr = mlx_png_file_to_image(ft_substr(line,
						3, ft_strlen(line) - 3 - lastLine));
		else if (ft_strncmp(line, "EA ", 3) == 0)
			game_data->textures->ea_txtr = mlx_png_file_to_image(ft_substr(line,
						3, ft_strlen(line) - 3 - lastLine));
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_rgb(line, game_data->textures->color_floor);
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_rgb(line, game_data->textures->color_ceiling);
		free(line);
		line = ft_get_next_line(fd);
		if (!game->textures->no_ptr || !game->textures->so_ptr
			|| !game->textures->we_ptr || !game->textures->ea_ptr)
			return (ft_error("init_textures",
					(char *[]){"Failed to create textures", NULL}));
	}
}

void	read_data(t_game **game_data, char *file)
{
	int	fd;

	if (init_data_structs(*game_data) != 0)
		return (free(*game_data), NULL);
	fd = open(file, O_RDONLY);
	get_data(*game_data, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	read_map(&(*game_data)->map, fd);
	close(fd);
	printf("Map Data:\n");
	for (int j = 0; (*game_data)->map && (*game_data)->map[j] != NULL; j++)
	{
		printf("%s\n", (*game_data)->map[j]);
	}
	printf("\nMap loaded successfully.\n");
	return (game_data);
}
