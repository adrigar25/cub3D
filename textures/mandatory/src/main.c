/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "map.h"
#include "parse.h"
#include "player.h"
#include "render.h"

/**
 * ENGLISH: Checks if a filename ends with the given extension.
 *
 * SPANISH: Comprueba si un nombre de archivo termina con la extensión dada.
 *
 * @param filename The name of the file to check. / El nombre del archivo.
 * @param extension The extension to check. / La extensión a comprobar.
 *
 * @return 1 if the extension matches, 0 otherwise. /
 * 		1 si la extensión coincide, 0 en caso contrario.
 */
int	valid_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len < extension_len)
		return (0);
	return (ft_strncmp(filename + filename_len - extension_len, extension,
			extension_len) == 0);
}

/**
 * ENGLISH: Initializes game data, reads the configuration file, validates
 * 			the map, sets up MLX and starts the game loop.
 *
 * SPANISH: Inicializa los datos del juego, lee el archivo de configuración,
 * 			valida el mapa, configura MLX e inicia el bucle del juego.
 *
 * @param file The path to the .cub configuration file. /
 * 		La ruta al archivo de configuración .cub.
 *
 * @return 0 on success, or 1 if an error occurred. /
 * 		0 en éxito, o 1 si ocurrió un error.
 */
int	cub3d(char *file)
{
	t_game	*game_data;

	game_data = init_data();
	if (read_data(&game_data, file))
		return (clear_game(game_data), 1);
	if (check_data(game_data))
		return (clear_game(game_data), 1);
	if (check_map(game_data->map.grid))
		return (clear_game(game_data), 1);
	if (init_mlx(game_data))
		return (clear_game(game_data), 1);
	if (load_textures_images(game_data))
		return (clear_game(game_data), 1);
	if (get_player_position(game_data))
		return (clear_game(game_data), 1);
	start_game_loop(game_data);
	clear_game(game_data);
	return (0);
}

/**
 * ENGLISH: Entry point of the program. Validates arguments and launches
 * 			the game.
 *
 * SPANISH: Punto de entrada del programa. Valida los argumentos e inicia
 * 			el juego.
 *
 * @param argc Number of command line arguments. / Número de argumentos.
 * @param argv Array of argument strings. / Array de cadenas de argumentos.
 *
 * @return 0 on success, or -1 if there was an error. /
 * 		0 en éxito, o -1 si hubo un error.
 */
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_fprintf(2, "Usage: %s <map_file.cub>\n", argv[0]);
		return (-1);
	}
	if (!valid_extension(argv[1], ".cub"))
	{
		ft_fprintf(2, RED "Error: Map file must have a .cub extension\n" RESET);
		return (-1);
	}
	return (cub3d(argv[1]));
}
