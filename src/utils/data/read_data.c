/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 15:45:18 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	get_data(t_game *game_data, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 8)
	{
		line = ft_get_next_line(fd);
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
	{
		free_map(game_data->map);
		free(game_data);
		close(fd);
		return ;
	}
}

t_game	*read_data(char *file)
{
	int		fd;
	t_game	*game_data;

	game_data = malloc(sizeof(t_game));
	if (!game_data)
		return (NULL);
	if (init_data_structs(game_data) != 0)
		return (free(game_data), NULL);
	fd = open(file, O_RDONLY);
	get_data(game_data, fd);
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
		printf("%s\n", game_data->map[j]);
	}
	printf("\nMap loaded successfully.\n");
	return (game_data);
}
