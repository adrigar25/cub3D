/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "render.h"
#include "mlx.h"

/**
 * ENGLISH: Initializes the image buffer for efficient pixel manipulation.
 * 			Creates an image in memory instead of drawing to the window.
 *
 * SPANISH: Inicializa el buffer de imagen para la manipulación eficiente
 * 			de píxeles. Crea una imagen en memoria en lugar de dibujar en
 * 			la ventana directamente.
 *
 * @param game Pointer to the game structure. / Puntero al juego.
 *
 * @return 1 on success, or 0 on failure. / 1 en éxito, o 0 en fallo.
 */
int	init_image_buffer(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx_ptr, WIN_W, WIN_H);
	if (!game->img.img)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		return (0);
	game->img.width = WIN_W;
	game->img.height = WIN_H;
	return (1);
}

/**
 * ENGLISH: Writes a pixel of the given color to the image buffer at (x, y).
 * 			Much faster than mlx_pixel_put as it writes directly to memory.
 *
 * SPANISH: Escribe un píxel del color dado en el buffer de imagen en (x, y).
 * 			Mucho más rápido que mlx_pixel_put al escribir directamente.
 *
 * @param img Pointer to the image structure. / Puntero a la imagen.
 * @param x X coordinate. / Coordenada X.
 * @param y Y coordinate. / Coordenada Y.
 * @param color Color in ARGB format. / Color en formato ARGB.
 */
void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * ENGLISH: Renders the completed frame from the image buffer to the window.
 * 			Call this once per frame after all pixel writes are done.
 *
 * SPANISH: Renderiza el frame completado desde el buffer de imagen hacia
 * 			la ventana. Llamar una vez por frame tras todas las escrituras.
 *
 * @param game Pointer to the game structure. / Puntero al juego.
 */
void	render_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}

/**
 * ENGLISH: Extracts the color of a pixel from a texture at coordinates (x, y).
 * 			Returns black if coordinates are out of bounds.
 *
 * SPANISH: Extrae el color de un píxel de una textura en (x, y).
 * 			Devuelve negro si las coordenadas están fuera de límites.
 *
 * @param texture Pointer to the texture image. / Puntero a la textura.
 * @param x X coordinate in the texture. / Coordenada X en la textura.
 * @param y Y coordinate in the texture. / Coordenada Y en la textura.
 *
 * @return The color value at (x, y). / El valor del color en (x, y).
 */
int	get_texture_color(t_img *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}
