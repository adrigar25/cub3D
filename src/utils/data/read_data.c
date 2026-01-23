/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/23 16:04:11 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

static int	load_img(t_game *game_data, char *path, char *dir)
{
	t_img	*text[4];
	t_img	*texture;

	text[0] = &game_data->textures.no;
	text[1] = &game_data->textures.so;
	text[2] = &game_data->textures.we;
	text[3] = &game_data->textures.ea;
	texture = NULL;
	if (!ft_strncmp(dir, "NO", 2))
		texture = text[0];
	else if (!ft_strncmp(dir, "SO", 2))
		texture = text[1];
	else if (!ft_strncmp(dir, "WE", 2))
		texture = text[2];
	else if (!ft_strncmp(dir, "EA", 2))
		texture = text[3];
	texture->img = mlx_xpm_file_to_image(game_data->mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (ft_fprintf(2, "\033[0;31m'Failed to load texture %s'\n", path),
			free(path), free(dir), -1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	return (free(path), free(dir), 0);
}

static int	get_data(t_game *game_data, int fd)
{
	char	*line;
	char	*trimmed;
	char	*value;

	line = ft_get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n");
		value = ft_strtrim(trimmed + 2, " \t\n");
		if (trimmed && is_texture_line(trimmed))
		{
			if (load_img(game_data, value, ft_substr(trimmed, 0, 2)) == -1)
				return (free(line), free(trimmed), -1);
		}
		else if (trimmed[0] == 'F' && game_data->textures.color_f == -1)
			game_data->textures.color_f = parse_rgb(value);
		else if (trimmed[0] == 'C' && game_data->textures.color_c == -1)
			game_data->textures.color_c = parse_rgb(value);
		free(trimmed);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (0);
}

int	read_data(t_game **game_data, char *file)
{
	int	fd;

	if (init_data_structs(*game_data) != 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "\033[0;31mFailed to open file\n"), -1);
	if (get_data(*game_data, fd) == -1)
		return (ft_fprintf(2, "\033[0;31mFailed to get data\n"), -1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "\033[0;31mFailed to reopen file\n"), -1);
	if (read_map(&(*game_data)->map, fd) == -1)
		return (ft_fprintf(2, "\033[0;31mFailed to read map\n"), -1);
	close(fd);
	return (0);
}
