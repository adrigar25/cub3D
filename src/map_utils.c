/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:11:03 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 22:38:20 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	line = ft_get_next_line(fd);
	while (line)
	{
		temp = ft_realloc(*map, sizeof(char *) * (i + 2));
		*map = temp;
		(*map)[i] = line;
		line = ft_get_next_line(fd);
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
