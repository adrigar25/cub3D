/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/07 16:10:58 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

static int	load_texture_image(t_game *game_data, char *path, char *dir)
{
	t_img	*texture;

	if (dir == NULL || path == NULL)
		return (-1);
	texture = NULL;
	if (ft_strncmp(dir, "NO", 2) == 0)
		texture = &game_data->textures.no;
	else if (ft_strncmp(dir, "SO", 2) == 0)
		texture = &game_data->textures.so;
	else if (ft_strncmp(dir, "WE", 2) == 0)
		texture = &game_data->textures.we;
	else if (ft_strncmp(dir, "EA", 2) == 0)
		texture = &game_data->textures.ea;
	if (texture && texture->img == NULL)
	{
		printf("Loading texture %s from path: %s\n", dir, path);
		texture->img = mlx_xpm_file_to_image(game_data->mlx_ptr, path,
				&texture->width, &texture->height);
		if (texture->img)
			texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
					&texture->line_len, &texture->endian);
	}
	else if (texture && texture->img != NULL)
		return (ft_fprintf(2, "\033[0;31mTexture %s is duplicated\n", dir), -1);
	free(path);
	free(dir);
	return (0);
}

static int	get_data(t_game *game_data, int fd)
{
	char	*line;
	int		last;
	char	*path;

	last = 0;
	line = ft_get_next_line(fd);
	while (line)
	{
		last = (line[ft_strlen(line) - 1] == '\n');
		if (is_texture_line(line))
		{
			path = ft_substr(line, 3, ft_strlen(line) - 3 - last);
			if (load_texture_image(game_data, path, ft_substr(line, 0, 2)) ==
				-1)
				return (-1);
		}
		else if (ft_strncmp(line, "F ", 2) == 0
			&& game_data->textures.color_floor == -1)
			game_data->textures.color_floor = parse_rgb(line);
		else if (ft_strncmp(line, "C ", 2) == 0
			&& game_data->textures.color_ceiling == -1)
			game_data->textures.color_ceiling = parse_rgb(line);
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
