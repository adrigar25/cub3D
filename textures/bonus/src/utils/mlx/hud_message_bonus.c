/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_message_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "libft.h"
#include "mlx.h"
#include "render_bonus.h"

/*
** Approximate char dimensions for MLX built-in font.
*/
#define HUD_CHAR_W 8
#define HUD_CHAR_H 13
#define HUD_PAD_X 24
#define HUD_PAD_Y 16

/**
 * ENGLISH: Renders a semi-transparent dark backdrop rectangle in the
 *          image buffer; each pixel is blended to 50% black.
 *
 * SPANISH: Renderiza un rectángulo de fondo semitransparente oscuro en
 *          el buffer de imagen; cada píxel se mezcla al 50% negro.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param r HUD rectangle bounds. / Límites del rectángulo del HUD.
 */
static void	draw_backdrop(t_game *game, t_hud_rect r)
{
	int	x;
	int	y;
	int	old;

	y = r.y0;
	while (y <= r.y1)
	{
		x = r.x0;
		while (x <= r.x1)
		{
			old = get_texture_color(&game->img, x, y);
			img_pixel_put(&game->img, x, y, (old >> 1) & 0x7F7F7F);
			x++;
		}
		y++;
	}
}

/**
 * ENGLISH: Draws one centred text line on the game window using the
 *          MLX built-in font. Must be called after the image is pushed.
 *
 * SPANISH: Dibuja una línea de texto centrada en la ventana del juego
 *          usando la fuente integrada de MLX. Debe llamarse tras volcar
 *          la imagen.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param msg Text string to draw. / Cadena de texto a dibujar.
 * @param row Screen row Y position. / Posición Y de fila en pantalla.
 * @param color Text colour (hex). / Color del texto (hexadecimal).
 */
static void	put_line(t_game *game, const char *msg, int row, int color)
{
	int	len;
	int	text_w;
	int	text_x;

	len = (int)ft_strlen(msg);
	text_w = len * HUD_CHAR_W;
	text_x = (WIN_W - text_w) / 2;
	mlx_string_put(game->mlx_ptr, game->win_ptr, text_x, row, color,
		(char *)msg);
}

/**
 * ENGLISH: Calculates the bounding box for the HUD overlay based on the
 *          title and optional sub-line string lengths.
 *
 * SPANISH: Calcula el bounding box del overlay del HUD en función de las
 *          longitudes de la cadena del título y las sublíneas opcionales.
 *
 * @param msg HUD message structure. / Estructura del mensaje HUD.
 *
 * @return t_hud_rect with the computed screen bounds. /
 *         t_hud_rect con los límites de pantalla calculados.
 */
static t_hud_rect	compute_rect(t_hud msg)
{
	t_hud_rect	r;
	int			box_w;
	int			box_h;

	box_w = (int)ft_strlen(msg.title) * HUD_CHAR_W;
	if ((int)ft_strlen(msg.sub) * HUD_CHAR_W > box_w)
		box_w = (int)ft_strlen(msg.sub) * HUD_CHAR_W;
	if ((int)ft_strlen(msg.sub2) * HUD_CHAR_W > box_w)
		box_w = (int)ft_strlen(msg.sub2) * HUD_CHAR_W;
	box_w += HUD_PAD_X * 2;
	box_h = HUD_CHAR_H + HUD_PAD_Y * 2;
	if (msg.sub)
		box_h += HUD_CHAR_H * 2;
	if (msg.sub2)
		box_h += HUD_CHAR_H * 2;
	r.x0 = (WIN_W - box_w) / 2;
	r.x1 = r.x0 + box_w;
	r.y0 = (WIN_H - box_h) / 2;
	r.y1 = r.y0 + box_h;
	return (r);
}

/**
 * ENGLISH: Renders the title, sub and sub2 text lines over the HUD
 *          backdrop using the computed row positions.
 *
 * SPANISH: Renderiza las líneas de texto del título, sub y sub2 sobre
 *          el fondo del HUD usando las posiciones de fila calculadas.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param msg HUD message structure. / Estructura del mensaje HUD.
 * @param r HUD rectangle bounds. / Límites del rectángulo del HUD.
 */
static void	draw_hud_lines(t_game *game, t_hud msg, t_hud_rect r)
{
	int	title_row;
	int	sub_row;
	int	sub2_row;

	title_row = r.y0 + HUD_PAD_Y;
	put_line(game, msg.title, title_row, msg.color);
	if (msg.sub)
	{
		sub_row = title_row + HUD_CHAR_H * 2;
		put_line(game, msg.sub, sub_row, 0xCCCCCC);
		if (msg.sub2)
		{
			sub2_row = sub_row + HUD_CHAR_H * 2;
			put_line(game, msg.sub2, sub2_row, 0xAAAAAA);
		}
	}
}

/**
 * ENGLISH: Public entry point: computes the overlay rect, draws the
 *          dimmed backdrop, pushes the image, then renders the text lines.
 *          msg.sub and msg.sub2 may be NULL.
 *
 * SPANISH: Punto de entrada público: calcula el rect del overlay, dibuja
 *          el fondo oscurecido, vuelca la imagen y renderiza las líneas.
 *          msg.sub y msg.sub2 pueden ser NULL.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param msg HUD message data (title, sub, sub2, color). /
 *            Datos del mensaje HUD (título, sub, sub2, color).
 */
void	draw_hud_message(t_game *game, t_hud msg)
{
	t_hud_rect	r;

	r = compute_rect(msg);
	draw_backdrop(game, r);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	draw_hud_lines(game, msg, r);
}
