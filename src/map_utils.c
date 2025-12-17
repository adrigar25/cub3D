/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:11:03 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 18:22:51 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/gnl/get_next_line.h"
#include "cub3d.h"
#include <fcntl.h>

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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
		temp = ft_realloc(*map, sizeof(char *) * (i + 2));
		*map = temp;
		(*map)[i] = line;
		line = get_next_line(fd);
		i++;
	}
	if (*map)
		(*map)[i] = NULL;
	close(fd);
	if (i > 256)
		return (free_map(*map), handle_error("Map too large"));
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (handle_error("Map is NULL"));
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(" 01NSEW\n", map[i][j]) == NULL)
				return (handle_error("Invalid character in map"));
			j++;
		}
		i++;
	}
	return (0);
}
