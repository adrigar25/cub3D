/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:58:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 01:14:10 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"
#include "../../sprite_helpers_bonus.h"

static int	is_transparent_color(t_img *texture, int color)
{
	int	key;

	if (!texture || !texture->addr)
		return (0);
	key = *(unsigned int *)texture->addr;
	return (color == key);
}

static int	compute_transform(t_game *game, double sprite_x, double sprite_y,
		double *out_tx, double *out_ty, int *out_screen_x)
{
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;

	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite_x - game->player.dir_x
			* sprite_y);
	transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	if (transform_y <= 0.0001)
		return (0);
	screen_x = (int)((WIN_W / 2.0) * (1 + transform_x / transform_y));
	*out_tx = transform_x;
	*out_ty = transform_y;
	*out_screen_x = screen_x;
	return (1);
}

typedef struct s_sprite_bounds
{
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		sprite_height;
	int		sprite_width;
	double	y0;
}			t_sprite_bounds;

static void	compute_bounds_and_size(t_img *texture, double transform_y,
		int screen_x, t_sprite_bounds *b, int pitch)
{
	int		height;
	int		width;
	double	y0;
	double	y1;

	height = (int)fabs(WIN_H / transform_y);
	if (texture->height > 0)
		width = (int)((double)height * (double)texture->width
				/ (double)texture->height);
	else
		width = height;
	if (height < 1)
		height = 1;
	if (width < 1)
		width = 1;
	y0 = -height / 2.0 + WIN_H / 2.0 + pitch;
	y1 = height / 2.0 + WIN_H / 2.0 + pitch;
	b->draw_start_y = (int)y0;
	b->draw_end_y = (int)y1;
	if (b->draw_start_y < 0)
		b->draw_start_y = 0;
	if (b->draw_end_y >= WIN_H)
		b->draw_end_y = WIN_H - 1;
	b->draw_start_x = -width / 2 + screen_x;
	if (b->draw_start_x < 0)
		b->draw_start_x = 0;
	b->draw_end_x = width / 2 + screen_x;
	if (b->draw_end_x >= WIN_W)
		b->draw_end_x = WIN_W - 1;
	b->sprite_height = height;
	b->sprite_width = width;
	b->y0 = y0;
}

static void	draw_columns(t_game *game, t_img *texture, t_sprite_bounds *b,
		double transform_y, int screen_x)
{
	int		stripe;
	int		tex_x;
	int		tex_y;
	double	rel_x;
	double	y_scale;
	int		color;
	int		y;

	stripe = b->draw_start_x;
	y_scale = (double)texture->height / (double)b->sprite_height;
	while (stripe <= b->draw_end_x)
	{
		if (transform_y >= game->zbuffer[stripe])
		{
			stripe++;
			continue ;
		}
		rel_x = (double)(stripe - (-b->sprite_width / 2 + screen_x));
		tex_x = (int)(rel_x * texture->width / (double)b->sprite_width);
		if (tex_x < 0 || tex_x >= texture->width)
		{
			stripe++;
			continue ;
		}
		y = b->draw_start_y;
		while (y <= b->draw_end_y)
		{
			tex_y = (int)(((double)y - b->y0) * y_scale);
			if (tex_y >= 0 && tex_y < texture->height)
			{
				color = get_texture_color(texture, tex_x, tex_y);
				if (!is_transparent_color(texture, color))
					img_pixel_put(&game->img, stripe, y, color);
			}
			y++;
		}
		stripe++;
	}
}

void	draw_sprite_at(t_game *game, t_img *texture, double world_x,
		double world_y)
{
	double			transform_x;
	double			transform_y;
	int				screen_x;
	t_sprite_bounds	b;
	double			local_x;
	double			local_y;

	local_x = world_x - game->player.pos_x;
	local_y = world_y - game->player.pos_y;
	if (!compute_transform(game, local_x, local_y, &transform_x, &transform_y,
			&screen_x))
		return ;
	compute_bounds_and_size(texture, transform_y, screen_x, &b,
		game->player.pitch);
	draw_columns(game, texture, &b, transform_y, screen_x);
}

static int	cmp_draw_sprite(const void *a, const void *b)
{
	const t_draw_sprite	*sa = (const t_draw_sprite *)a;
	const t_draw_sprite	*sb = (const t_draw_sprite *)b;

	if (sa->depth < sb->depth)
		return (1);
	if (sa->depth > sb->depth)
		return (-1);
	return (0);
}

void	render_sprites(t_game *game)
{
	int				count;
	t_draw_sprite	*list;
	int				i;
	t_sprite_window	window;

	if (!game || !game->map)
		return ;
	sprite_compute_scan_window(game, &window);
	count = sprite_count_total_in_window(game, &window);
	if (count == 0)
		return ;
	list = (t_draw_sprite *)malloc(sizeof(t_draw_sprite) * count);
	if (!list)
		return ;
	i = 0;
	i = sprite_append_map_sprites(game, &window, list, i);
	i = sprite_append_enemy_sprites(game, &window, list, i);
	if (i == 0)
	{
		free(list);
		return ;
	}
	qsort(list, i, sizeof(t_draw_sprite), cmp_draw_sprite);
	count = 0;
	while (count < i)
	{
		draw_sprite_at(game, list[count].tex, list[count].x, list[count].y);
		count++;
	}
	free(list);
}
