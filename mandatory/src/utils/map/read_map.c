/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:06:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include "game.h"
#include "console.h"
#include <stdlib.h>

static int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0] || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 10NSWE\n\t", line[i]))
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

static int	process_line(char ***map, int *i, char *line, int *started)
{
	if (!*started && !is_map_line(line))
		return (0);
	if (!is_map_line(line))
		return (-1);
	*started = 1;
	if (add_line(map, (*i)++, line) == -1)
		return (-1);
	return (0);
}

static int	validate_map_size(char ***map, int i)
{
	if (i > 256)
		return (ft_fprintf(2, RED "Error: Map too large\n" RESET), -1);
	if (*map)
		(*map)[i] = NULL;
	return (0);
}

int	read_map(char ***map, int fd)
{
	char	*line;
	int		i;
	int		started;
	int		result;

	i = 0;
	started = 0;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		result = process_line(map, &i, line, &started);
		free(line);
		if (result == -1)
			break ;
	}
	return (validate_map_size(map, i));
}
