/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "map.h"
#include <stdlib.h>

/**
 * ENGLISH: Returns 1 if the given line contains only valid map characters.
 *
 * SPANISH: Devuelve 1 si la línea contiene solo caracteres válidos del mapa.
 *
 * @param line The line to check. / La línea a comprobar.
 *
 * @return 1 if the line is a map line, 0 otherwise. /
 * 		1 si la línea es del mapa, 0 en caso contrario.
 */
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

/**
 * ENGLISH: Appends a new line to the map array, resizing it as needed.
 *
 * SPANISH: Añade una nueva línea al array del mapa, redimensionándolo.
 *
 * @param map Pointer to the map array. / Puntero al array del mapa.
 * @param index Current number of lines. / Número actual de líneas.
 * @param line The line to add. / La línea a añadir.
 *
 * @return 0 on success, or -1 on malloc failure. /
 * 		0 en éxito, o -1 si falla el malloc.
 */
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
	(*map)[index + 1] = NULL;
	return (0);
}

/**
 * ENGLISH: Processes one line: skips non-map lines before the map starts,
 * 			then adds map lines to the array.
 *
 * SPANISH: Procesa una línea: omite líneas no-mapa antes del mapa,
 * 			luego añade las líneas del mapa al array.
 *
 * @param map Pointer to the map array. / Puntero al array del mapa.
 * @param i Pointer to the current line count. / Puntero al contador.
 * @param line The line to process. / La línea a procesar.
 * @param started Flag indicating if the map has started. /
 * 		Bandera que indica si el mapa ha comenzado.
 *
 * @return 0 on success, or -1 on error. / 0 en éxito, o -1 en error.
 */
static int	process_line(char ***map, int *i, char *line, int *started)
{
	if (!*started && !is_map_line(line))
		return (0);
	*started = 1;
	if (add_line(map, (*i)++, line) == -1)
		return (-1);
	return (0);
}

/**
 * ENGLISH: Validates that the map does not exceed 256 rows and sets
 * 			the final NULL terminator.
 *
 * SPANISH: Valida que el mapa no supere 256 filas y establece el
 * 			terminador NULL final.
 *
 * @param map Pointer to the map array. / Puntero al array del mapa.
 * @param i Total number of lines read. / Número total de líneas leídas.
 *
 * @return 0 if valid, or -1 if the map is too large. /
 * 		0 si es válido, o -1 si el mapa es demasiado grande.
 */
static int	validate_map_size(char ***map, int i)
{
	if (i > 256)
		return (ft_fprintf(2, RED "Error: Map too large\n" RESET), -1);
	if (*map)
		(*map)[i] = NULL;
	return (0);
}

/**
 * ENGLISH: Reads all map lines from the file descriptor and stores them
 * 			in a NULL-terminated array of strings.
 *
 * SPANISH: Lee todas las líneas del mapa desde el descriptor de archivo
 * 			y las almacena en un array de cadenas terminado en NULL.
 *
 * @param map
 * 		ENGLISH: Pointer to the map array to populate.
 * 		SPANISH: Puntero al array del mapa a rellenar.
 * @param fd
 * 		ENGLISH: File descriptor of the file to read.
 * 		SPANISH: Descriptor de archivo del fichero a leer.
 *
 * @return
 * 		ENGLISH: 0 on success, or -1 if there was an error.
 * 		SPANISH: 0 en éxito, o -1 si hubo un error.
 */
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
		{
			ft_get_next_line(-1);
			break ;
		}
	}
	return (validate_map_size(map, i));
}
