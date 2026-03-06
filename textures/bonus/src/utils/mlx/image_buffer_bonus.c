/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "mlx.h"
#include "render_bonus.h"

/**
 * ENGLISH: Initialises the image buffer for efficient pixel manipulation.
 *          Creates an MLX image in memory instead of drawing directly to
 *          the window.
 *
 * SPANISH: Inicializa el buffer de imagen para manipulación eficiente de
 *          píxeles. Crea una imagen MLX en memoria en lugar de dibujar
 *          directamente a la ventana.
 *
 * @param mlx_ptr MLX instance pointer. / Puntero a la instancia MLX.
 * @param img Pointer to the image structure to fill. /
 *            Puntero a la estructura de imagen a rellenar.
 * @param width Image width in pixels. / Ancho de la imagen en píxeles.
 * @param height Image height in pixels. / Alto de la imagen en píxeles.
 *
 * @return 1 on success, 0 on failure. / 1 en éxito, 0 en fallo.
 */
int	init_image_buffer(void *mlx_ptr, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx_ptr, width, height);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (0);
	img->width = width;
	img->height = height;
	return (1);
}

/**
 * ENGLISH: Puts a pixel in the image buffer at (x, y) with the given
 *          colour. Much faster than mlx_pixel_put as it writes directly
 *          to memory.
 *
 * SPANISH: Coloca un píxel en el buffer de imagen en (x, y) con el
 *          color dado. Mucho más rápido que mlx_pixel_put al escribir
 *          directamente en memoria.
 *
 * @param img Pointer to the image structure. /
 *            Puntero a la estructura de imagen.
 * @param x X coordinate. / Coordenada X.
 * @param y Y coordinate. / Coordenada Y.
 * @param color Colour value in ARGB format. / Valor de color en ARGB.
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
 * ENGLISH: Renders the complete frame from the image buffer to the window.
 *          Call once per frame after all pixel manipulations are done.
 *
 * SPANISH: Renderiza el fotograma completo desde el buffer de imagen a la
 *          ventana. Llamar una vez por frame tras todas las manipulaciones.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	render_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}

/**
 * ENGLISH: Returns the colour stored at (x, y) in a texture image.
 *          Safely clamps coordinates before reading from the data buffer.
 *
 * SPANISH: Retorna el color almacenado en (x, y) de una imagen de textura.
 *          Limita de forma segura las coordenadas antes de leer el buffer.
 *
 * @param texture Pointer to the texture image structure. /
 *                Puntero a la estructura de imagen de textura.
 * @param x X coordinate in the texture. / Coordenada X en la textura.
 * @param y Y coordinate in the texture. / Coordenada Y en la textura.
 *
 * @return Colour value at the given coordinates. /
 *         Valor de color en las coordenadas dadas.
 */
int	get_texture_color(t_img *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}
