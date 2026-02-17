/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_message_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 22:53:38 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Approximate char dimensions for MLX built-in font.
*/
#define HUD_CHAR_W 8
#define HUD_CHAR_H 13
#define HUD_PAD_X 24
#define HUD_PAD_Y 16

/*
** Blend a dark colour (50 % opacity black) over a pixel already in the buffer.
*/
static int	blend_dark(int src)
{
	return ((src >> 1) & 0x7F7F7F);
}

/*
** Draw a semi-transparent dark rectangle in the image buffer.
*/
static void	draw_backdrop(t_game *game, int x0, int y0, int x1, int y1)
{
	int	x;
	int	y;
	int	old;

	y = y0;
	while (y <= y1)
	{
		x = x0;
		while (x <= x1)
		{
			old = get_texture_color(&game->img, x, y);
			img_pixel_put(&game->img, x, y, blend_dark(old));
			x++;
		}
		y++;
	}
}

/*
** Draw one line of @msg centred horizontally at screen row @row using
** mlx_string_put (called AFTER the image is pushed to the window).
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

/*
** draw_hud_message – render a centred overlay message on screen.
**
** @game   : game context
** @title  : main line (larger visual weight via colour)
** @sub    : secondary line shown below (pass NULL to skip)
** @color  : colour for the title text (e.g. 0x00FF00 green, 0xFF4444 red)
**
** The function blends a dark box into the current image buffer, pushes it to
** the window, then overlays the text with mlx_string_put.
** Call render_frame() yourself first if you want the 3-D scene as background,
** or call this standalone – it will push whatever is currently in game->img.
*/
void	draw_hud_message(t_game *game, const char *title, const char *sub,
		const char *sub2, int color)
{
	int	title_len;
	int	sub_len;
	int	sub2_len;
	int	box_w;
	int	box_h;
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	title_row;
	int	sub_row;
	int	sub2_row;

	title_len = (int)ft_strlen(title);
	sub_len = sub ? (int)ft_strlen(sub) : 0;
	sub2_len = sub2 ? (int)ft_strlen(sub2) : 0;
	box_w = title_len * HUD_CHAR_W;
	if (sub_len * HUD_CHAR_W > box_w)
		box_w = sub_len * HUD_CHAR_W;
	if (sub2_len * HUD_CHAR_W > box_w)
		box_w = sub2_len * HUD_CHAR_W;
	box_w += HUD_PAD_X * 2;
	box_h = HUD_CHAR_H + HUD_PAD_Y * 2;
	if (sub)
		box_h += HUD_CHAR_H * 2;
	if (sub2)
		box_h += HUD_CHAR_H * 2;
	x0 = (WIN_W - box_w) / 2;
	x1 = x0 + box_w;
	y0 = (WIN_H - box_h) / 2;
	y1 = y0 + box_h;
	draw_backdrop(game, x0, y0, x1, y1);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	title_row = y0 + HUD_PAD_Y;
	put_line(game, title, title_row, color);
	if (sub)
	{
		sub_row = title_row + HUD_CHAR_H * 2;
		put_line(game, sub, sub_row, 0xCCCCCC);
		if (sub2)
		{
			sub2_row = sub_row + HUD_CHAR_H * 2;
			put_line(game, sub2, sub2_row, 0xAAAAAA);
		}
	}
}
