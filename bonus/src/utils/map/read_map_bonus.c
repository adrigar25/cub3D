/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "enemy_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Scans a map line for the first character not in the
 *          allowed-characters list and returns its column index.
 *
 * SPANISH: Escanea una línea de mapa buscando el primer carácter que no
 *          esté en la lista de carácteres permitidos y retorna su columna.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param line The map line to scan. / La línea de mapa a escanear.
 *
 * @return Column index of the bad char, or -1 if all chars are valid. /
 *         Índice de columna del carácter erróneo, o -1 si todos son válidos.
 */
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

/**
 * ENGLISH: Returns 1 if a line contains only characters from the
 *          allowed-characters list and is not empty or a bare newline.
 *
 * SPANISH: Retorna 1 si una línea contiene solo caracteres de la lista de
 *          permitidos y no está vacía ni es solo un salto de línea.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param line The line to test. / La línea a probar.
 *
 * @return 1 if valid map line, 0 otherwise. /
 *         1 si es línea de mapa válida, 0 en caso contrario.
 */
int	is_map_line(t_game *game, char *line)
{
	if (!line || !line[0] || line[0] == '\n')
		return (0);
	if (find_bad_col(game, line) >= 0)
		return (0);
	return (1);
}

/**
 * ENGLISH: Prints a descriptive error message for an invalid map line,
 *          identifying the offending character and its position.
 *
 * SPANISH: Imprime un mensaje de error descriptivo para una línea de
 *          mapa inválida, identificando el carácter erróneo y su posición.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param line The invalid line. / La línea inválida.
 * @param index Row index in the map. / Índice de fila en el mapa.
 *
 * @return Always -1. / Siempre -1.
 */
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

/**
 * ENGLISH: Validates and appends one map row to the dynamic grid,
 *          updating the maximum column width.
 *
 * SPANISH: Valida y añade una fila de mapa a la cuadrícula dinámica,
 *          actualizando el ancho máximo de columna.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param index Current row index. / Índice de fila actual.
 * @param line Raw line string. / Cadena de línea sin procesar.
 * @param max_width Pointer to the current maximum width. /
 *                  Puntero al ancho máximo actual.
 *
 * @return 0 on success, -1 on error. / 0 en éxito, -1 en error.
 */
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

/**
 * ENGLISH: Reads the map section from the open file descriptor, starting
 *          from the first map line, building the grid, and collecting
 *          enemies from 'X' tiles.
 *
 * SPANISH: Lee la sección del mapa desde el descriptor de archivo abierto,
 *          comenzando desde la primera línea de mapa, construye la
 *          cuadrícula y recoge los enemigos de las casillas 'X'.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param fd Open file descriptor. / Descriptor de archivo abierto.
 * @param first_line First map line (already read). /
 *                   Primera línea de mapa (ya leída).
 *
 * @return 0 on success, -1 on error. / 0 en éxito, -1 en error.
 */
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
