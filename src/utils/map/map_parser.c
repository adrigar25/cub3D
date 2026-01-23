/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/23 16:22:56 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_valid_map_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!ft_strchr(" 10NSWE", line[j]))
			return (0);
		j++;
	}
	return (1);
}

static int	alloc_map_line(char ***map, int i, char *line)
{
	char	**temp;

	temp = ft_realloc(*map, sizeof(char *) * i, sizeof(char *) * (i + 2));
	if (!temp)
		return (free(line), free_map(*map), ft_error("read_map",
				(char *[]){"Memory allocation failed", NULL}), -1);
	*map = temp;
	(*map)[i] = ft_strtrim(line, "\n");
	if (!(*map)[i])
		return (free(line), free_map(*map), ft_error("read_map",
				(char *[]){"Memory allocation failed", NULL}), -1);
	return (0);
}

static int	process_line(char ***map, int *i, int *map_started)
{
	if ((*map)[*i][0] == '\0')
	{
		if (!*map_started)
			free((*map)[*i]);
		else
			(*i)++;
	}
	else if (is_valid_map_line((*map)[*i]))
	{
		*map_started = 1;
		(*i)++;
	}
	else
	{
		if (*map_started)
			return ((*i)++, 0);
		free((*map)[*i]);
	}
	return (1);
}

int	read_map(char ***map, int fd)
{
	int		i;
	char	*line;
	int		map_started;

	i = 0;
	map_started = 0;
	*map = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		if (alloc_map_line(map, i, line) == -1)
			return (-1);
		free(line);
		if (!process_line(map, &i, &map_started))
			break ;
		line = ft_get_next_line(fd);
	}
	if (*map)
		(*map)[i] = NULL;
	if (i > 256)
		return (ft_error("read_map", (char *[]){"Map too large", NULL}), -1);
	return (0);
}
