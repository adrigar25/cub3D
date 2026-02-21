/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_message_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 16:47:25 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx.h"
#include "game_bonus.h"
#include "libft.h"
#include "render_bonus.h"

/*
** Approximate char dimensions for MLX built-in font.
*/
#define HUD_CHAR_W 8
#define HUD_CHAR_H 13
#define HUD_PAD_X 24
#define HUD_PAD_Y 16

/*
** Draw a semi-transparent dark rectangle in the image buffer.
** Pixel colour is blended to 50 % black: (src >> 1) & 0x7F7F7F.
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
** compute_rect  – calculate the bounding box for the HUD overlay.
** draw_hud_lines – render title / sub / sub2 over the pushed window.
** draw_hud_message – public entry point; msg.sub / msg.sub2 may be NULL.
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

void	draw_hud_message(t_game *game, t_hud msg)
{
	t_hud_rect	r;

	r = compute_rect(msg);
	draw_backdrop(game, r);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	draw_hud_lines(game, msg, r);
}
