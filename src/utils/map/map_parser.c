/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 15:18:29 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	read_map(char ***map, int fd)
{
	int		i;
	char	*line;
	char	**temp;

	i = 0;
	*map = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		temp = ft_realloc(*map, sizeof(char *) * i, sizeof(char *) * (i + 2));
		if (!temp)
			return (free_map(*map), ft_error("read_map",
				(char *[]){"Memory allocation failed", NULL}));
		*map = temp;
		(*map)[i] = ft_strtrim(line, '\n');
		if (!(*map)[i])
			return (free(line), free_map(*map),
				ft_error("read_map",
					(char *[]){"Memory allocation failed", NULL}));
		free(line);
		line = ft_get_next_line(fd);
		i++;
	}
	if (*map)
		(*map)[i] = NULL;
	if (i > 256)
		return (free_map(*map), ft_error("read_map",
			(char *[]){"Map too large", NULL}));
	return (0);
}
