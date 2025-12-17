/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 00:19:35 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/gnl/get_next_line.h"
#include "../cub3d.h"

int	read_map(char ***map, int fd)
{
	int		i;
	char	*line;
	char	**temp;

	i = 0;
	*map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_realloc(*map, sizeof(char *) * i, sizeof(char *) * (i + 2));
		if (!temp)
			return (free_map(*map), handle_error("Memory allocation failed"));
		*map = temp;
		(*map)[i] = ft_strtrim(line, "\n");
		if (!(*map)[i])
			return (free(line), free_map(*map),
				handle_error("ft_strtrim failed"));
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (*map)
		(*map)[i] = NULL;
	if (i > 256)
		return (free_map(*map), handle_error("Map too large"));
	return (0);
}
