/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 18:58:21 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * ENGLISH: Initialize the image buffer for efficient pixel manipulation.
 *          Creates an image in memory instead of drawing directly to window.
 *
 * SPANISH: Inicializa el buffer de imagen para manipulación eficiente de píxeles.
 *          Crea una imagen en memoria en lugar de dibujar directamente a la ventana.
 *
 * @param game Pointer to the game structure
 * @return 1 on success, 0 on failure
 */
int	init_image_buffer(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.img)
		return (0);

	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
										&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img);
		return (0);
	}

	// Inicializar dimensiones del buffer principal
	game->img.width = WINDOW_WIDTH;
	game->img.height = WINDOW_HEIGHT;

	return (1);
}

/**
 * ENGLISH: Put a pixel in the image buffer at coordinates (x, y) with given color.
 *          Much faster than mlx_pixel_put as it writes directly to memory.
 *
 * SPANISH: Coloca un píxel en el buffer de imagen en coordenadas (x, y) con el color dado.
 *          Mucho más rápido que mlx_pixel_put ya que escribe directamente en memoria.
 *
 * @param img Pointer to the image structure
 * @param x X coordinate
 * @param y Y coordinate
 * @param color Color in RGB format
 */
void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

/**
 * ENGLISH: Render the complete frame from image buffer to the window.
 *          Call this once per frame after all pixel manipulations are done.
 *
 * SPANISH: Renderiza el frame completo desde el buffer de imagen a la ventana.
 *          Llama a esto una vez por frame después de todas las manipulaciones de píxeles.
 *
 * @param game Pointer to the game structure
 */
void	render_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}

/**
 * ENGLISH: Get color from texture at specific coordinates.
 *          Safely extracts pixel color from texture image data.
 *
 * SPANISH: Obtiene color de la textura en coordenadas específicas.
 *          Extrae de forma segura el color del píxel de los datos de la imagen de textura.
 *
 * @param texture Pointer to texture image structure
 * @param x X coordinate in texture (0 to TEX_WIDTH-1)
 * @param y Y coordinate in texture (0 to TEX_HEIGHT-1)
 * @return Color value at specified coordinates
 */
int	get_texture_color(t_img *texture, int x, int y)
{
	char	*dst;

	if (!texture || !texture->addr)
		return (0x000000);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);

	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int*)dst);
}
