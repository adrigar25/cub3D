/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:01:25 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "minimap_bonus.h"
#include "mlx.h"
#include "render_bonus.h"
#include <math.h>

/**
 * ENGLISH: Computes the world coordinates for a minimap pixel and
 *          draws the appropriate tile colour if inside the circle.
 *
 * SPANISH: Calcula las coordenadas del mundo para un píxel del minimapa
 *          y dibuja el color de casilla adecuado si está dentro del círculo.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param px Pixel X in the minimap image. / Píxel X en la imagen del minimapa.
 * @param py Pixel Y in the minimap image. / Píxel Y en la imagen del minimapa.
 */
static void	draw_minimap_point(t_game *game, int px, int py)
{
	double		c[2];
	double		rel_x;
	double		rel_y;
	double		dist;
	t_fcoord	world;

	c[0] = game->minimap.width / 2.0;
	c[1] = game->minimap.height / 2.0;
	rel_x = px - c[0];
	rel_y = py - c[1];
	dist = sqrt(rel_x * rel_x + rel_y * rel_y);
	if (dist <= c[0] - MINIMAP_BORDER)
	{
		world.x = (-rel_y * game->player.dir_x - rel_x * game->player.dir_y)
			/ (MINIMAP_SCALE / 2) + game->player.pos_x;
		world.y = (-rel_y * game->player.dir_y + rel_x * game->player.dir_x)
			/ (MINIMAP_SCALE / 2) + game->player.pos_y;
		put_minimap_tile(game, px, py, world);
	}
}

/**
 * ENGLISH: Iterates over every pixel of the minimap image and calls
 *          draw_minimap_point to fill in the rotated world view.
 *
 * SPANISH: Itera sobre cada píxel de la imagen del minimapa y llama a
 *          draw_minimap_point para rellenar la vista del mundo rotada.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
static void	draw_rotated_minimap(t_game *game)
{
	int	px;
	int	py;

	py = 0;
	while (py < game->minimap.height)
	{
		px = 0;
		while (px < game->minimap.width)
		{
			draw_minimap_point(game, px, py);
			px++;
		}
		py++;
	}
}

/**
 * ENGLISH: Copies a single pixel from the minimap image buffer into the
 *          main frame buffer at the given offset.
 *
 * SPANISH: Copia un píxel individual del buffer de imagen del minimapa
 *          al buffer de fotograma principal con el desplazamiento dado.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param px Source pixel X. / Píxel X de origen.
 * @param py Source pixel Y. / Píxel Y de origen.
 * @param off Array [off_x, off_y] destination offset. /
 *            Array [off_x, off_y] de desplazamiento destino.
 */
static void	blit_pixel(t_game *game, int px, int py, int off[2])
{
	char	*src;
	char	*dst;

	src = game->minimap.addr + (py * game->minimap.line_len + px
			* (game->minimap.bpp / 8));
	dst = game->img.addr + ((off[1] + py) * game->img.line_len + (off[0] + px)
			* (game->img.bpp / 8));
	*(unsigned int *)dst = *(unsigned int *)src;
}

/**
 * ENGLISH: Copies the circular minimap image onto the main frame buffer
 *          at the specified screen offset.
 *
 * SPANISH: Copia la imagen circular del minimapa al buffer de fotograma
 *          principal en el desplazamiento de pantalla especificado.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param off_x Horizontal offset on the screen. /
 *              Desplazamiento horizontal en pantalla.
 * @param off_y Vertical offset on the screen. /
 *              Desplazamiento vertical en pantalla.
 */
static void	blit_minimap(t_game *game, int off_x, int off_y)
{
	int		px;
	int		py;
	double	cx;
	double	dist;
	int		off[2];

	cx = game->minimap.width / 2.0;
	off[0] = off_x;
	off[1] = off_y;
	py = 0;
	while (py < game->minimap.height)
	{
		px = 0;
		while (px < game->minimap.width)
		{
			dist = sqrt((px - cx) * (px - cx) + (py - cx) * (py - cx));
			if (dist <= cx)
				blit_pixel(game, px, py, off);
			px++;
		}
		py++;
	}
}

/**
 * ENGLISH: Orchestrates the full minimap render: clears the buffer, draws
 *          the rotated world, draws the player triangle, then blits the
 *          result to the screen corner.
 *
 * SPANISH: Orquesta el renderizado completo del minimapa: limpia el buffer,
 *          dibuja el mundo rotado, dibuja el triángulo del jugador, luego
 *          vuelca el resultado a la esquina de la pantalla.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Always 0. / Siempre 0.
 */
int	render_minimap(t_game *game)
{
	int	minimap_x;
	int	minimap_y;

	minimap_x = WIN_W - MINIMAP_W - 10;
	minimap_y = WIN_H - MINIMAP_H - 10;
	clear_map(game);
	draw_rotated_minimap(game);
	draw_player(game, game->minimap.width / 2.0, game->minimap.height / 2.0);
	blit_minimap(game, minimap_x, minimap_y);
	return (0);
}
