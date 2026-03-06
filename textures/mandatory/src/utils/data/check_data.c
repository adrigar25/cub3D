/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/22 19:44:06 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>

/**
 * ENGLISH: Checks if the texture files specified in the game data exist and are
 * 			accessible. It also checks if the floor and ceiling colors are
 * 			valid.
 *
 * SPANISH: Verifica si los archivos de textura especificados en los datos del
 * 			juego existen y son accesibles. También verifica si los colores del
 * 			piso y el techo son válidos.
 *
 * @param path The file path of the texture to check. / La ruta del archivo de
 * 			la textura a verificar.
 * @param direction The direction associated with the texture
 * 			(e.g., "North", "South"). / La dirección asociada con la textura
 * 			(por ejemplo, "Norte", "Sur").
 *
 * @return 0 if the texture file exists and is accessible, or -1 if it does not.
 * 		/ 0 si el archivo de textura existe y es accesible, o -1 si no lo es.
 */
static int	check_texture_file(char *path, char *direction)
{
	if (!path || access(path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: %s texture file not found\n" RESET,
			direction);
		return (-1);
	}
	return (0);
}

/**
 * ENGLISH: Checks if the floor and ceiling colors in the game data are valid.
 * 			It verifies that both colors are set and that they are in the
 * 			correct format.
 *
 * SPANISH: Verifica si los colores del piso y el techo en los datos del juego
 * 			son válidos. Verifica que ambos colores estén establecidos y que
 * 			estén en el formato correcto.
 *
 * @param game A pointer to the game structure containing the textures and
 * 			colors to be checked. / Un puntero a la estructura del juego que
 * 			contiene las texturas y colores a verificar.
 *
 * @return 0 if both colors are valid, or -1 if either color is missing or
 * 		invalid. / 0 si ambos colores son válidos, o -1 si falta alguno de los
 * 		colores o es inválido.
 */
static int	check_colors(t_game *game)
{
	if (game->textures.color_f == -1 || game->textures.color_c == -1)
	{
		ft_fprintf(2, RED "Error: Missing floor or ceiling color\n" RESET);
		return (-1);
	}
	if (game->textures.color_c == -2)
		return (ft_fprintf(2, RED "Error: Invalid ceiling RGB\n" RESET), -1);
	if (game->textures.color_f == -2)
		return (ft_fprintf(2, RED "Error: Invalid floor RGB\n" RESET), -1);
	return (0);
}

/**
 * ENGLISH: Checks the validity of the game data, including texture file paths
 * 			and color values. It ensures that all required textures are present
 * 			and that the floor and ceiling colors are properly defined.
 *
 * SPANISH: Verifica la validez de los datos del juego, incluyendo las rutas de
 * 			los archivos de textura y los valores de color. Asegura que todas
 * 			las texturas requeridas estén presentes y que los colores del piso
 * 			y el techo estén correctamente definidos.
 *
 * @param game_data A pointer to the game structure containing the textures and
 * 			colors to be checked. / Un puntero a la estructura del juego que
 * 			contiene las texturas y colores a verificar.
 *
 * @return 0 if all data is valid, or -1 if any texture file is missing or if
 * 		any color value is invalid. / 0 si todos los datos son válidos, o -1
 * 		si falta algún archivo de textura o si algún valor de color es inválido.
 */
int	check_data(t_game *game_data)
{
	if (check_texture_file(game_data->textures.path_no, "North") == -1)
		return (-1);
	if (check_texture_file(game_data->textures.path_so, "South") == -1)
		return (-1);
	if (check_texture_file(game_data->textures.path_we, "West") == -1)
		return (-1);
	if (check_texture_file(game_data->textures.path_ea, "East") == -1)
		return (-1);
	if (check_colors(game_data) == -1)
		return (-1);
	return (0);
}
