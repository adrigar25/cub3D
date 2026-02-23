/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:03:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "game.h"
#include "libft.h"
#include "mlx.h"
#include "render.h"

/**
 * ENGLISH: Loads a single XPM texture image from the given path into the
 * 			provided image structure.
 *
 * SPANISH: Carga una imagen de textura XPM desde la ruta dada en la
 * 			estructura de imagen proporcionada.
 *
 * @param game Pointer to the game structure. / Puntero al juego.
 * @param img Pointer to the image structure to fill. / Puntero a la imagen.
 * @param path Path to the XPM texture file. / Ruta al archivo XPM.
 *
 * @return 0 on success, or -1 if loading failed. /
 * 		0 en éxito, o -1 si la carga falló.
 */
static int	load_texture(t_game *game, t_img *img, char *path)
{
	if (!path)
		return (ft_fprintf(2, RED "Error: Texture path is NULL\n" RESET), -1);
	img->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
		return (ft_fprintf(2, RED "Error: Loading img %s\n" RESET, path), -1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

/**
 * ENGLISH: Loads the four wall textures (North, South, West, East) from
 * 			the paths stored in the game data.
 *
 * SPANISH: Carga las cuatro texturas de pared (Norte, Sur, Oeste, Este)
 * 			desde las rutas almacenadas en los datos del juego.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 *
 * @return 0 if all textures loaded, or -1 if any failed. /
 * 		0 si se cargaron todas, o -1 si alguna falló.
 */
int	load_textures_images(t_game *game)
{
	if (load_texture(game, &game->textures.no, game->textures.path_no) == -1)
		return (-1);
	if (load_texture(game, &game->textures.so, game->textures.path_so) == -1)
		return (-1);
	if (load_texture(game, &game->textures.we, game->textures.path_we) == -1)
		return (-1);
	if (load_texture(game, &game->textures.ea, game->textures.path_ea) == -1)
		return (-1);
	return (0);
}

/**
 * ENGLISH: Initializes the MLX library, creates the window and the image
 * 			buffer used for rendering.
 *
 * SPANISH: Inicializa la librería MLX, crea la ventana y el buffer de
 * 			imagen usado para el renderizado.
 *
 * @param game Pointer to the game structure. / Puntero a la estructura
 * 		del juego.
 *
 * @return 0 on success, or -1 if any initialization step failed. /
 * 		0 en éxito, o -1 si algún paso de inicialización falló.
 */
int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_fprintf(2, "Error: Failed to initialize MLX\n"), -1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "Cub3D");
	if (!game->win_ptr)
		return (ft_fprintf(2, "Error: Failed to create window\n"), -1);
	if (!init_image_buffer(game))
		return (ft_fprintf(2, "Error: Failed to create image buffer\n"), -1);
	return (0);
}
