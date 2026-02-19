/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"
#include "parse_bonus.h"
#include <fcntl.h>

/**
 * ENGLISH: Read configuration data from file until map starts.
 *
 * SPANISH: Lee datos de configuración del archivo hasta que comienza el mapa.
 */
static int	get_data(t_game *game_data, int fd, char **first_map_line) {
  char *line;
  int result;

  result = 0;
  if (!game_data)
    return (-1);
  *first_map_line = NULL;
  while (result != -1 && !*first_map_line) {
    line = ft_get_next_line(fd);
    if (!line)
      break ;
    if (is_map_line(game_data, line)) {
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
int	read_data(t_game **game_data, char *file) {
  int fd;
  char *first_line;

  fd = open(file, O_RDONLY);
  if (fd == -1)
    return (ft_fprintf(2, RED "Error: Cannot open file\n" RESET), -1);
  first_line = NULL;
  if (get_data(*game_data, fd, &first_line) == -1) {
    close(fd);
    return (ft_fprintf(2, RED "Error: Failed to read data\n" RESET), -1);
  }
  if (read_map(*game_data, fd, first_line) == -1) {
    close(fd);
    return (ft_fprintf(2, RED "Error: Failed to read map\n" RESET), -1);
  }
  close(fd);
  return (0);
}
