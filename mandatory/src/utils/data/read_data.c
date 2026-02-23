/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:04:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:10:59 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "map.h"
#include "parse.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * ENGLISH: Reads the game configuration data from a specified file, including
 * 			texture paths and color values. It processes each line of the file
 * 			to store the relevant information in the game data structure. After
 * 			reading the configuration, it also reads the map data from the same
 * 			file.
 *
 * SPANISH: Lee los datos de configuración del juego desde un archivo
 * 			especificado, incluyendo las rutas de las texturas y los valores de
 * 			color. Procesa cada línea del archivo para almacenar la información
 * 			relevante en la estructura de datos del juego. Después de leer la
 * 			configuración, también lee los datos del mapa desde el mismo
 * 			archivo.
 *
 * @param game_data A pointer to the game structure where the configuration data
 * 		will be stored. / Un puntero a la estructura del juego donde se
 * 		almacenarán los datos de configuración.
 * @param path The file path of the configuration file to read. / La ruta del
 * 		archivo de configuración a leer.
 * @param dir The direction associated with the texture
 * 		(e.g., "NO", "SO", "WE", "EA"). / La dirección asociada con la textura
 * 		(por ejemplo, "NO", "SO", "WE", "EA").
 *
 * @return 0 if the data was read successfully, or -1 if there was an error. /
 */
static int	store_path(t_game *game_data, char *path, char *dir)
{
	char	**dest;
	char	*trimmed;

	dest = NULL;
	if (!ft_strcmp(dir, "NO"))
		dest = &game_data->textures.path_no;
	else if (!ft_strcmp(dir, "SO"))
		dest = &game_data->textures.path_so;
	else if (!ft_strcmp(dir, "WE"))
		dest = &game_data->textures.path_we;
	else if (!ft_strcmp(dir, "EA"))
		dest = &game_data->textures.path_ea;
	if (!dest)
		return (0);
	if (*dest != NULL)
	{
		ft_fprintf(2, RED "Error: Duplicated texture: %s\n" RESET, path);
		return (-1);
	}
	trimmed = ft_strtrim(path, " \t\n");
	*dest = ft_strdup(trimmed);
	if (!*dest)
		return (free(trimmed), -1);
	return (free(trimmed), 0);
}

/**
 * ENGLISH: Processes a single line of the configuration file to extract and
 * 			storenthe relevant data, such as texture paths or color values. It
 * 			determines the type of data based on the key and calls the
 * 			appropriate function to handle it.
 *
 * SPANISH: Procesa una sola línea del archivo de configuración para extraer y
 * 			almacenar los datos relevantes, como las rutas de las texturas o los
 * 			valores de color. Determina el tipo de dato basado en la clave y
 * 			llama a la función apropiada para manejarlo.
 *
 * @param game_data A pointer to the game structure where the extracted data
 * 		will be stored. / Un puntero a la estructura del juego donde se
 * 		almacenarán los datos extraídos.
 * @param line A string containing the line from the configuration file to be
 * 		processed. / Una cadena que contiene la línea del archivo de
 * 		configuración que se va a procesar.
 *
 * @return 0 if the line was processed successfully, or -1 if there was an
 * 		error. / 0 si la línea se procesó correctamente, o -1 si hubo un error.
 */
int	process_color(t_game *game, char *key, char *value)
{
	int	*color;

	color = NULL;
	if (!ft_strcmp(key, "C"))
		color = &game->textures.color_c;
	else if (!ft_strcmp(key, "F"))
		color = &game->textures.color_f;
	if (*color != -1)
	{
		ft_fprintf(2, RED "Error: Duplicated color:%s\n" RESET, key);
		return (-1);
	}
	*color = parse_rgb(value);
	return (*color);
}

/**
 * ENGLISH: Reads the configuration data from the specified file descriptor,
 * 			line by line, and processes each line to extract texture paths and
 * 			color values. It continues until it encounters an error or reaches
 * 			the end of the file.
 *
 * SPANISH: Lee los datos de configuración desde el descriptor de archivo
 * 			especificado, línea por línea, y procesa cada línea para extraer las
 * 			rutas de las texturas y los valores de color. Continúa hasta que
 * 			encuentra un error o llega al final del archivo.
 *
 * @param game_data A pointer to the game structure where the extracted data
 * 		will be stored. / Un puntero a la estructura del juego donde se
 * 		almacenarán los datos extraídos.
 * @param line The line of the configuration file to process. / La línea del
 * 		archivo de configuración a procesar.
 *
 * @return 0 if the line was processed successfully, or -1 if there was an
 * 		error. / 0 si la línea se procesó correctamente, o -1 si hubo un error.
 */
static int	process_config_line(t_game *game_data, char *line)
{
	char	*temp;
	char	*raw_key;
	char	*key;
	char	*value;
	int		result;

	result = 0;
	temp = ft_strtrim(line, " \t\n");
	if (!temp || temp[0] == '\0')
		return (free(temp), 0);
	raw_key = ft_substr(temp, 0, 2);
	if (!raw_key)
		return (free(temp), 0);
	key = ft_strtrim(raw_key, " \t\n");
	value = ft_strtrim(temp + 2, " \t\n");
	if (!key || !value)
		return (free(temp), free(raw_key), free(key), free(value), 0);
	if (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"))
		result = process_color(game_data, key, value);
	else
		result = store_path(game_data, value, key);
	return (free(temp), free(raw_key), free(key), free(value), result);
}

/**
 * ENGLISH: Reads the game configuration data from the specified file
 * 			descriptor, line by line, and processes each line to extract texture
 * 			paths and color values. It continues until it encounters an error or
 * 			reaches the end of the file.
 *
 * SPANISH: Lee los datos de configuración desde el descriptor de archivo
 * 			especificado, línea por línea, y procesa cada línea para extraer las
 * 			rutas de las texturas y los valores de color. Continúa hasta que
 * 			encuentra un error o llega al final del archivo.
 *
 * @param game_data A pointer to the game structure where the extracted data
 * 		will be stored. / Un puntero a la estructura del juego donde se
 * 		almacenarán los datos extraídos.
 * @param fd The file descriptor of the configuration file to read. / El
 * 		descriptor de archivo del archivo de configuración a leer.
 *
 * @return 0 if the data was read successfully, or -1 if there was an error. /
 * 		0 si los datos se leyeron correctamente, o -1 si hubo un error.
 */
static int	get_data(t_game *game_data, int fd)
{
	char	*line;
	int		result;

	result = 0;
	if (!game_data)
		return (-1);
	while (result != -1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		result = process_config_line(game_data, line);
		free(line);
	}
	if (result == -1)
		ft_get_next_line(-1);
	return (result);
}

/**
 * ENGLISH: Reads the game configuration data and map data from the specified
 * 			file. It first reads the configuration data to extract texture paths
 * 			and color values, and then reads the map data to populate the game
 * 			map structure.
 *
 * SPANISH: Lee los datos de configuración del juego y los datos del mapa desde
 * 			el archivo especificado. Primero lee los datos de configuración para
 * 			extraer las rutas de las texturas y los valores de color, y luego
 * 			lee los datos del mapa para llenar la estructura del mapa del juego.
 *
 * @param game_data A pointer to the game structure where the extracted data will
 * 		be stored. / Un puntero a la estructura del juego donde se
 * 		almacenarán los datos extraídos.
 * @param file The file path of the configuration file to read. /
 * 		La ruta del archivo de configuración a leer.
 *
 * @return 0 if the data was read successfully, or -1 if there was an
 * 		error. / 0 si los datos se leyeron correctamente, o -1 si hubo un error.
 */
int	read_data(t_game **game_data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, RED "Error: Cannot open file\n" RESET), -1);
	if (get_data(*game_data, fd) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read data\n" RESET), -1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, RED "Error: Cannot open file\n" RESET), -1);
	if (read_map(&(*game_data)->map.grid, fd) == -1)
	{
		close(fd);
		return (ft_fprintf(2, RED "Error: Failed to read map\n" RESET), -1);
	}
	close(fd);
	return (0);
}
