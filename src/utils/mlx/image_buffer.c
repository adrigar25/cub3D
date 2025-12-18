/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 17:24:20 by adriescr         ###   ########.fr       */
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
