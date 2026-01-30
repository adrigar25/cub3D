/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/29 23:42:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static int	is_texture_line(char *line)
{
	return (!ft_strcmp(line, "NO") || !ft_strcmp(line, "SO") || !ft_strcmp(line,
			"WE") || !ft_strcmp(line, "EA") || !ft_strcmp(line, "DO"));
}

static int	store_path(t_game *game_data, char *path, char *dir)
{
	char	**dest;
	char	*trimmed;

	dest = NULL;
	if (!ft_strcmp(dir, "NO"))
		dest = &game_data->textures.path_no;
	else if (!ft_strcmp(dir, "SO"))
		dest = &game_data->textures.path_so;
	else if (!ft_strcmp(dir, "WE"))
		dest = &game_data->textures.path_we;
	else if (!ft_strcmp(dir, "EA"))
		dest = &game_data->textures.path_ea;
	else if (!ft_strcmp(dir, "DO"))
		dest = &game_data->textures.path_door;
	if (!dest)
		return (0);
	if (*dest != NULL)
		return (ft_fprintf(2, RED "Error: Duplicated texture: %s\n" RESET,
				path), 0);
	trimmed = ft_strtrim(path, " \t\n");
	*dest = ft_strdup(trimmed);
	if (!*dest)
		return (free(trimmed), -1);
	return (free(trimmed), 0);
}

static int	process_line(t_game *game_data, char *line)
{
	char	*temp;
	char	*key;
	char	*value;
	int		result;

	result = 0;
	temp = ft_strtrim(line, " \t\n");
	if (!temp)
		return (0);
	key = ft_substr(temp, 0, 2);
	value = ft_strtrim(line + 2, " \t\n");
	if (!key || !value)
		return (free(key), free(value), free(temp), 0);
	if (key[0] == 'F' && game_data->textures.color_f == -1)
		game_data->textures.color_f = parse_rgb(value);
	else if (key[0] == 'C' && game_data->textures.color_c == -1)
		game_data->textures.color_c = parse_rgb(value);
	else if (is_texture_line(key))
		result = store_path(game_data, value, key);
	free(temp);
	free(key);
	free(value);
	return (result);
}

static int	get_data(t_game *game_data, int fd)
{
	char	*line;
	int		result;

	result = 0;
	if (!game_data)
		return (-1);
	while (result != -1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		result = process_line(game_data, line);
		free(line);
	}
	return (result);
}

int	read_data(t_game **game_data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, RED "Error: Cannot open file\n" RESET), -1);
	if (get_data(*game_data, fd) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read data\n" RESET), -1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, RED "Error: Cannot open file\n" RESET), -1);
	if (read_map(*game_data, fd) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read map\n" RESET), -1);
	}
	close(fd);
	return (0);
}
