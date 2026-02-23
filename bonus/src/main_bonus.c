/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "parse_bonus.h"
#include "player_bonus.h"
#include "render_bonus.h"

/**
 * ENGLISH: Checks if the given filename has the expected extension.
 *
 * SPANISH: Comprueba si el nombre de archivo tiene la extensión esperada.
 *
 * @param filename The name of the file to check. /
 *                 El nombre del archivo a comprobar.
 * @param extension The expected extension (e.g. ".cub"). /
 *                  La extensión esperada (p.ej. ".cub").
 *
 * @return 1 if the extension matches, 0 otherwise. /
 *         1 si la extensión coincide, 0 en caso contrario.
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
 * ENGLISH: Initialises and runs the full cub3D game pipeline: parse,
 *          validate, load MLX resources, place player and start loop.
 *
 * SPANISH: Inicializa y ejecuta el pipeline completo de cub3D: parsear,
 *          validar, cargar recursos MLX, colocar jugador e iniciar bucle.
 *
 * @param file Path to the .cub map file. /
 *             Ruta al archivo de mapa .cub.
 *
 * @return 0 on success, 1 on error. / 0 en éxito, 1 en error.
 */
int	cub3d(char *file)
{
	t_game	*game_data;

	game_data = init_data();
	if (read_data(&game_data, file))
		return (clear_game(game_data, -1), 1);
	if (check_data(game_data))
		return (clear_game(game_data, -1), 1);
	if (check_map(game_data))
		return (clear_game(game_data, -1), 1);
	if (init_mlx(game_data))
		return (clear_game(game_data, -1), 1);
	if (load_images(game_data))
		return (clear_game(game_data, -1), 1);
	if (get_player_position(game_data))
		return (clear_game(game_data, -1), 1);
	start_game_loop(game_data);
	clear_game(game_data, 0);
	return (0);
}

/**
 * ENGLISH: Entry point. Validates argument count and file extension,
 *          then launches the game.
 *
 * SPANISH: Punto de entrada. Valida el número de argumentos y la
 *          extensión del archivo, luego lanza el juego.
 *
 * @param argc Number of arguments. / Número de argumentos.
 * @param argv Array of argument strings. / Array de cadenas de argumentos.
 *
 * @return 0 on success, -1 on invalid arguments. /
 *         0 en éxito, -1 en argumentos inválidos.
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
