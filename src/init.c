/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:40:42 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 18:50:29 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/gnl/get_next_line.h"
#include "cub3d.h"

static void	parse_rgb(char *line, int *color)
{
	char	*first_comma;
	char	*second_comma;

	first_comma = ft_strchr(line, ',');
	second_comma = ft_strchr(first_comma + 1, ',');
	color[0] = ft_atoi(line + 2);
	color[1] = ft_atoi(first_comma + 1);
	color[2] = ft_atoi(second_comma + 1);
}

int	init_data_structs(t_game *game)
{
	game->color_floor = malloc(3 * sizeof(int));
	game->color_ceiling = malloc(3 * sizeof(int));
	if (!game->color_floor || !game->color_ceiling)
	{
		free(game->color_floor);
		free(game->color_ceiling);
		return (-1);
	}
	game->texture_north = NULL;
	game->texture_south = NULL;
	game->texture_west = NULL;
	game->texture_east = NULL;
	game->color_floor[0] = -1;
	game->color_floor[1] = -1;
	game->color_floor[2] = -1;
	game->color_ceiling[0] = -1;
	game->color_ceiling[1] = -1;
	game->color_ceiling[2] = -1;
	game->map = NULL;
	return (0);
}

t_game	*init_game(char *file)
{
	int		i;
	char	*line;
	int		fd;
	t_game	*game_data;

	i = 0;
	game_data = malloc(sizeof(t_game));
	if (!game_data)
		return (NULL);
	if (init_data_structs(game_data) != 0)
		return (free(game_data), NULL);
	fd = open(file, O_RDONLY);
	while (i < 8)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i == 0)
			game_data->texture_north = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (i == 1)
			game_data->texture_south = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (i == 2)
			game_data->texture_west = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (i == 3)
			game_data->texture_east = ft_substr(line, 3, ft_strlen(line) - 4);
		else if (i == 5)
			parse_rgb(line, game_data->color_floor);
		else if (i == 6)
			parse_rgb(line, game_data->color_ceiling);
		free(line);
		i++;
	}
	if (read_map(&game_data->map, fd) == -1)
		return (free_map(game_data->map), free(game_data), NULL);
	close(fd);
	printf("North Texture: %s\n", game_data->texture_north);
	printf("South Texture: %s\n", game_data->texture_south);
	printf("West Texture: %s\n", game_data->texture_west);
	printf("East Texture: %s\n", game_data->texture_east);
	printf("Floor Color: R=%d, G=%d, B=%d\n", game_data->color_floor[0],
		game_data->color_floor[1], game_data->color_floor[2]);
	printf("Ceiling Color: R=%d, G=%d, B=%d\n", game_data->color_ceiling[0],
		game_data->color_ceiling[1], game_data->color_ceiling[2]);
	printf("Map Data:\n");
	for (int j = 0; game_data->map && game_data->map[j] != NULL; j++)
	{
		printf("%s", game_data->map[j]);
	}
	printf("\nMap loaded successfully.\n");
	return (game_data);
}
