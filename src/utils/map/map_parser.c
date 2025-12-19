/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/19 13:48:18 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_valid_map_line(char *line)
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

int	read_map(char ***map, int fd)
{
	int		i;
	char	*line;
	char	**temp;
	int		map_started;

	i = 0;
	map_started = 0;
	*map = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		temp = ft_realloc(*map, sizeof(char *) * i, sizeof(char *) * (i + 2));
		if (!temp)
			return (free(line), free_map(*map), ft_error("read_map",
					(char *[]){"Memory allocation failed", NULL}), -1);
		*map = temp;
		(*map)[i] = ft_strtrim(line, '\n');
		if (!(*map)[i])
			return (free(line), free_map(*map), ft_error("read_map",
					(char *[]){"Memory allocation failed", NULL}), -1);
		free(line);
		if ((*map)[i][0] == '\0')
		{
			if (!map_started)
			{
				free((*map)[i]);
				line = ft_get_next_line(fd);
				continue ;
			}
			else
			{
				line = ft_get_next_line(fd);
				i++;
				continue ;
			}
		}
		if (is_valid_map_line((*map)[i]))
		{
			map_started = 1;
			line = ft_get_next_line(fd);
			i++;
		}
		else
		{
			if (!map_started)
			{
				free((*map)[i]);
				line = ft_get_next_line(fd);
				continue ;
			}
			else
			{
				i++;
				break ;
			}
		}
	}
	if (*map)
		(*map)[i] = NULL;
	if (i > 256)
		return (free_map(*map), ft_error("read_map", (char *[]){"Map too large",
				NULL}), -1);
	return (0);
}
