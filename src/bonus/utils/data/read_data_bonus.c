/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/05 22:31:10 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static int	push_texture(t_game *game, t_texture *new_texture)
{
	t_texture	*current;

	if (!game->sprites)
	{
		game->sprites = new_texture;
		return (0);
	}
	current = game->sprites;
	while (current->next)
		current = current->next;
	current->next = new_texture;
	return (0);
}

static int	process_texture(t_game *game, char *key, char *value)
{
	t_texture	*new_texture;
	char		c;
	int			exists;

	new_texture = malloc(sizeof(t_texture));
	if (!new_texture)
		return (-1);
	new_texture->name = ft_strtrim(key, " \t\n");
	new_texture->path = ft_strdup(value);
	new_texture->next = NULL;
	ft_fprintf(2, "DBG texture key='%s' value='%s'\n", key, value);
	if (!ft_strcmp(key, "SO"))
		game->txt_so = new_texture;
	else if (!ft_strcmp(key, "NO"))
		game->txt_no = new_texture;
	else if (!ft_strcmp(key, "WE"))
		game->txt_we = new_texture;
	else if (!ft_strcmp(key, "EA"))
		game->txt_ea = new_texture;
	else if (!ft_strcmp(key, "DO"))
		game->txt_door = new_texture;
	else if (!ft_strcmp(key, "X1"))
		game->e_txt_s = new_texture;
	else if (!ft_strcmp(key, "X2"))
		game->e_txt_w1 = new_texture;
	else if (!ft_strcmp(key, "X3"))
		game->e_txt_w2 = new_texture;
	else
	{
		push_texture(game, new_texture);
		if (new_texture->name && new_texture->name[0])
		{
			c = new_texture->name[0];
			exists = 0;
			for (int i = 0; i < game->allowed_count; ++i)
				if (game->allowed_chars[i] == c)
					exists = 1;
			if (!exists
				&& game->allowed_count < (int)sizeof(game->allowed_chars) - 1)
			{
				game->allowed_chars[game->allowed_count++] = c;
				game->allowed_chars[game->allowed_count] = '\0';
			}
		}
	}
	return (0);
}

static int	process_line(t_game *game, char *line)
{
	char	*temp;
	char	*key;
	char	*key2;
	char	*value;
	int		result;

	result = 0;
	temp = ft_strtrim(line, " \t\n");
	if (!temp || temp[0] == '\0')
		return (free(temp), 0);
	key = ft_substr(temp, 0, 2);
	key2 = ft_strtrim(key, " \t\n");
	value = ft_strtrim(temp + 2, " \t\n");
	if (!ft_strcmp(key2, "C"))
		game->ceiling_color = parse_rgb(value);
	else if (!ft_strcmp(key2, "F"))
		game->floor_color = parse_rgb(value);
	else
		result = process_texture(game, key2, value);
	printf("DBG processed line: key='%s' value='%s'\n", key2, value);
	free(temp);
	free(key);
	free(key2);
	free(value);
	return (result);
}

static int	get_data(t_game *game_data, int fd, char **first_map_line)
{
	char	*line;
	int		result;

	result = 0;
	if (!game_data)
		return (-1);
	*first_map_line = NULL;
	while (result != -1 && !*first_map_line)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (is_map_line(game_data, line))
		{
			*first_map_line = line;
			break ;
		}
		result = process_line(game_data, line);
		free(line);
	}
	return (result);
}

int	read_data(t_game **game_data, char *file)
{
	int		fd;
	char	*first_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, RED "Error: Cannot open file\n" RESET), -1);
	first_line = NULL;
	if (get_data(*game_data, fd, &first_line) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read data\n" RESET), -1);
	}
	if (read_map(*game_data, fd, first_line) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read map\n" RESET), -1);
	}
	close(fd);
	return (0);
}
