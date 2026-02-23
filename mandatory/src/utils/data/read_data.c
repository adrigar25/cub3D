/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/22 19:15:38 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "map.h"
#include "parse.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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
	if (!dest)
		return (0);
	if (*dest != NULL)
	{
		ft_fprintf(2, RED "Error: Duplicated texture: %s\n" RESET, path);
		return (-1);
	}
	trimmed = ft_strtrim(path, " \t\n");
	*dest = ft_strdup(trimmed);
	if (!*dest)
		return (free(trimmed), -1);
	return (free(trimmed), 0);
}

int	process_color(t_game *game, char *key, char *value)
{
	int	*color;

	color = NULL;
	if (!ft_strcmp(key, "C"))
		color = &game->textures.color_c;
	else if (!ft_strcmp(key, "F"))
		color = &game->textures.color_f;
	if (*color != -1)
	{
		ft_fprintf(2, RED "Error: Duplicated color:%s\n" RESET, key);
		return (-1);
	}
	*color = parse_rgb(value);
	return (*color);
}

static int	process_config_line(t_game *game_data, char *line)
{
	char	*temp;
	char	*raw_key;
	char	*key;
	char	*value;
	int		result;

	result = 0;
	temp = ft_strtrim(line, " \t\n");
	if (!temp || temp[0] == '\0')
		return (free(temp), 0);
	raw_key = ft_substr(temp, 0, 2);
	if (!raw_key)
		return (free(temp), 0);
	key = ft_strtrim(raw_key, " \t\n");
	value = ft_strtrim(temp + 2, " \t\n");
	if (!key || !value)
		return (free(temp), free(raw_key), free(key), free(value), 0);
	if (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"))
		result = process_color(game_data, key, value);
	else
		result = store_path(game_data, value, key);
	return (free(temp), free(raw_key), free(key), free(value), result);
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
		result = process_config_line(game_data, line);
		free(line);
	}
	if (result == -1)
		ft_get_next_line(-1);
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
	if (read_map(&(*game_data)->map.grid, fd) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read map\n" RESET), -1);
	}
	close(fd);
	return (0);
}
