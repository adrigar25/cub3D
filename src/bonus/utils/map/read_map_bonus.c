/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/05 15:59:25 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static int	is_allowed_char(t_game *game, char c)
{
	int	i;

	if (!game)
		return (0);
	i = 0;
	while (i < game->allowed_count)
	{
		if (game->allowed_chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_map_line(t_game *game, char *line)
{
	int	i;

	if (!line || !line[0] || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i])
	{
		if (!is_allowed_char(game, line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	add_line(char ***map, int index, char *line)
{
	char	**new_map;

	new_map = ft_realloc(*map, sizeof(char *) * index, sizeof(char *) * (index
				+ 2));
	if (!new_map)
		return (-1);
	*map = new_map;
	(*map)[index] = ft_strtrim(line, "\n");
	if (!(*map)[index])
		return (-1);
	return (0);
}

static int	process_line(t_game *game, char ***map, int *i, char *line,
		int *started)
{
	if (!*started && !is_map_line(game, line))
		return (0);
	if (!is_map_line(game, line))
		return (-1);
	*started = 1;
	if (add_line(map, (*i)++, line) == -1)
		return (-1);
	return (0);
}

static int	validate_map_size(char ***map, int i)
{
	return (0);
	if (i > 256)
		return (ft_fprintf(2, RED "Error: Map too large\n" RESET), -1);
	if (*map)
		(*map)[i] = NULL;
	return (0);
}

int	read_map(t_game *game, int fd, char *first_line)
{
	char	*line;
	int		i;
	int		started;
	int		result;
	int		max_width;

	i = 0;
	started = 0;
	max_width = 0;
	if (first_line)
	{
		if ((int)ft_strlen(first_line) > max_width)
			max_width = ft_strlen(first_line);
		result = process_line(game, &game->map, &i, first_line, &started);
		free(first_line);
		if (result == -1)
		{
			game->map_h = i;
			game->map_w = max_width;
			return (validate_map_size(&game->map, i));
		}
	}
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if ((int)ft_strlen(line) > max_width)
			max_width = ft_strlen(line);
		result = process_line(game, &game->map, &i, line, &started);
		free(line);
		if (result == -1)
			break ;
	}
	game->map_h = i;
	game->map_w = max_width;
    /* Recoger enemigos del mapa (carácter 'X') */
    enemy_collect_from_map(game);
	return (validate_map_size(&game->map, i));
}
