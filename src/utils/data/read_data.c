/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/19 13:48:25 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	load_texture_image(t_game *game_data, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game_data->mlx_ptr, path,
			&texture->width, &texture->height);
	if (texture->img)
	{
		texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
				&texture->line_len, &texture->endian);
	}
}

static int	get_data(t_game *game_data, int fd)
{
	char	*line;
	char	*path;
	int		lastLine;

	lastLine = 0;
	line = ft_get_next_line(fd);
	while (line)
	{
		lastLine = (line[ft_strlen(line) - 1] == '\n');
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			path = ft_substr(line, 3, ft_strlen(line) - 3 - lastLine);
			load_texture_image(game_data, &game_data->textures.no, path);
			free(path);
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			path = ft_substr(line, 3, ft_strlen(line) - 3 - lastLine);
			load_texture_image(game_data, &game_data->textures.so, path);
			free(path);
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			path = ft_substr(line, 3, ft_strlen(line) - 3 - lastLine);
			load_texture_image(game_data, &game_data->textures.we, path);
			free(path);
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			path = ft_substr(line, 3, ft_strlen(line) - 3 - lastLine);
			load_texture_image(game_data, &game_data->textures.ea, path);
			free(path);
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
			game_data->textures.color_floor = parse_rgb(line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			game_data->textures.color_ceiling = parse_rgb(line);
		free(line);
		line = ft_get_next_line(fd);
	}
	if (!game_data->textures.no.img || !game_data->textures.so.img
		|| !game_data->textures.we.img || !game_data->textures.ea.img)
		return (ft_error("init_textures",
				(char *[]){"Failed to create textures", NULL}), -1);
	return (0);
}

int	read_data(t_game **game_data, char *file)
{
	int	fd;

	if (init_data_structs(*game_data) != 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error("read_data", (char *[]){"Failed to open file", NULL}),
			-1);
	if (get_data(*game_data, fd) == -1)
		return (ft_error("read_data", (char *[]){"Failed to read data", NULL}),
			-1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error("read_data", (char *[]){"Failed to open file", NULL}),
			-1);
	if (read_map(&(*game_data)->map, fd) == -1)
		return (ft_error("read_data", (char *[]){"Failed to read map", NULL}),
			-1);
	close(fd);
	return (0);
}
