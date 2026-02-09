/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/09 16:56:25 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

/**
 * ENGLISH: Read configuration data from file until map starts.
 *
 * SPANISH: Lee datos de configuración del archivo hasta que comienza el mapa.
 */
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
		result = process_config_line(game_data, line);
		free(line);
	}
	return (result);
}

/**
 * ENGLISH: Main function to read and parse the configuration file.
 *
 * SPANISH: Función principal para leer y parsear el archivo de configuración.
 */
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
