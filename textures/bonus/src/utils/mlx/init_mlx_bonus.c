/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:03:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "minimap_bonus.h"
#include "mlx.h"
#include "render_bonus.h"

/**
 * ENGLISH: Loads a single texture from disk via MLX and retrieves its
 *          pixel data address.
 *
 * SPANISH: Carga una única textura desde disco mediante MLX y recupera
 *          la dirección de datos de píxeles.
 *
 * @param mlx MLX instance pointer. / Puntero a la instancia MLX.
 * @param texture Pointer to the texture to load. /
 *                Puntero a la textura a cargar.
 *
 * @return 0 on success, -1 on failure. / 0 en éxito, -1 en fallo.
 */
static int	load_texture(void *mlx, t_texture *texture)
{
	char	*path;
	t_img	*img;

	if (!texture)
		return (ft_fprintf(2, RED "Error: Texture is NULL\n" RESET), -1);
	path = texture->path;
	img = &texture->img;
	if (!path)
		return (ft_fprintf(2, RED "Error: Texture path is NULL\n" RESET), -1);
	if (!img)
		return (ft_fprintf(2, RED "Error: Image structure is NULL\n" RESET),
			-1);
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img)
		return (ft_fprintf(2, RED "Error: Loading img %s\n" RESET, path), -1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

/**
 * ENGLISH: Iterates over the sprite linked list and loads each texture
 *          from disk.
 *
 * SPANISH: Itera sobre la lista enlazada de sprites y carga cada textura
 *          desde disco.
 *
 * @param mlx MLX instance pointer. / Puntero a la instancia MLX.
 * @param sprites Head of the sprite texture list. /
 *                Cabeza de la lista de texturas de sprite.
 *
 * @return 0 on success, -1 if any texture fails to load. /
 *         0 en éxito, -1 si alguna textura falla al cargarse.
 */
static int	load_sprites(void *mlx, t_texture *sprites)
{
	t_texture	*current;

	if (!sprites)
		return (0);
	current = sprites;
	while (current)
	{
		if (load_texture(mlx, current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

/**
 * ENGLISH: Loads all game textures (walls, door, enemy, exit, sprites)
 *          into MLX image objects.
 *
 * SPANISH: Carga todas las texturas del juego (paredes, puerta, enemigo,
 *          salida, sprites) en objetos de imagen MLX.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 0 on success, -1 if any texture fails. /
 *         0 en éxito, -1 si alguna textura falla.
 */
int	load_images(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	if (game->txt_door && load_texture(mlx, game->txt_door) == -1)
		return (-1);
	if (game->e_txt_s && load_texture(mlx, game->e_txt_s) == -1)
		return (-1);
	if (game->e_txt_w1 && load_texture(mlx, game->e_txt_w1) == -1)
		return (-1);
	if (game->e_txt_w2 && load_texture(mlx, game->e_txt_w2) == -1)
		return (-1);
	if (load_texture(mlx, game->txt_no) == -1)
		return (-1);
	if (load_texture(mlx, game->txt_so) == -1)
		return (-1);
	if (load_texture(mlx, game->txt_ea) == -1)
		return (-1);
	if (load_texture(mlx, game->txt_we) == -1)
		return (-1);
	if (game->txt_exit && load_texture(mlx, game->txt_exit) == -1)
		return (-1);
	if (load_sprites(mlx, game->sprites) == -1)
		return (-1);
	return (0);
}

/**
 * ENGLISH: Initialises MLX, creates the game window and allocates both
 *          the main frame buffer and the minimap image buffer.
 *
 * SPANISH: Inicializa MLX, crea la ventana del juego y reserva tanto el
 *          buffer de fotograma principal como el buffer de imagen del
 *          minimapa.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 0 on success, -1 on error. / 0 en éxito, -1 en error.
 */
int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_fprintf(2, "Error: Failed to initialize MLX\n"), -1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "Cub3D");
	if (!game->win_ptr)
		return (ft_fprintf(2, "Error: Failed to create window\n"), -1);
	if (!init_image_buffer(game->mlx_ptr, &game->img, WIN_W, WIN_H))
		return (ft_fprintf(2, "Error: Failed to create image buffer\n"), -1);
	if (!init_image_buffer(game->mlx_ptr, &game->minimap, MINIMAP_W, MINIMAP_H))
		return (ft_fprintf(2, "Error: Failed to create minimap buffer\n"), -1);
	return (0);
}
