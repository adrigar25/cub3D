/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/22 18:56:34 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "enemy_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"
#include <stdlib.h>

static int	find_bad_col(t_game *game, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (j < game->allowed_count && game->allowed_chars[j] != line[i])
			j++;
		if (j >= game->allowed_count)
			return (i);
		i++;
	}
	return (-1);
}

int	is_map_line(t_game *game, char *line)
{
	if (!line || !line[0] || line[0] == '\n')
		return (0);
	if (find_bad_col(game, line) >= 0)
		return (0);
	return (1);
}

static int	report_invalid_line(t_game *game, char *line, int index)
{
	int	col;

	col = -1;
	if (line)
		col = find_bad_col(game, line);
	if (col >= 0 && line[col] == 'X')
	{
		ft_fprintf(2, RED "Error: Enemy 'X' at row %d, col %d", index + 1, col
			+ 1);
		ft_fprintf(2, " requires X1/X2/X3 textures\n" RESET);
	}
	else if (col >= 0)
	{
		ft_fprintf(2, RED "Error: invalid character ");
		ft_fprintf(2, "'%c' at row %d, col %d" RESET "\n", line[col], index + 1,
			col + 1);
	}
	else
		ft_fprintf(2, RED "Error: invalid map line" RESET "\n");
	return (-1);
}

static int	add_line(t_game *game, int index, char *line, size_t *max_width)
{
	char	**new_map;

	if (!is_map_line(game, line))
		return (report_invalid_line(game, line, index));
	if (ft_strlen(line) > *max_width)
		*max_width = ft_strlen(line);
	new_map = ft_realloc(game->map.grid, sizeof(char *) * index, sizeof(char *)
			* (index + 2));
	if (!new_map)
		return (-1);
	game->map.grid = new_map;
	game->map.grid[index] = ft_strtrim(line, "\n");
	if (!game->map.grid[index])
		return (-1);
	game->map.grid[index + 1] = NULL;
	return (0);
}

int	read_map(t_game *game, int fd, char *first_line)
{
	char	*line;
	int		i;
	size_t	max_width;

	i = -1;
	max_width = 0;
	if (!first_line)
		return (-1);
	line = ft_strdup(first_line);
	free(first_line);
	while (1)
	{
		if (++i > 0)
			line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (add_line(game, i, line, &max_width) == -1)
			return (free(line), ft_get_next_line(-1), -1);
		free(line);
	}
	game->map.height = i;
	game->map.width = (int)max_width;
	enemy_collect_from_map(game);
	return (0);
}
