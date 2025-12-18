/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:57:57 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 17:32:02 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		ft_draw_start(t_game *game, int line_height)
{
	int	draw_start;

	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

int		ft_draw_end(t_game *game, int line_height)
{
	int	draw_end;

	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	return (draw_end);
}

void	draw_column(t_game *game, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	wall_color;

	line_height = game->raycast.line_height;
	draw_start = ft_draw_start(game, line_height);
	draw_end = ft_draw_end(game, line_height);

	// Determinar color de la pared basado en la dirección (sin operador ternario)
	if (game->raycast.side == 0)  // Pared vertical (norte/sur)
	{
		if (game->raycast.ray_dir_x > 0)
			wall_color = 0xFF0000;  // Rojo
		else
			wall_color = 0x800000;  // Rojo oscuro
	}
	else  // Pared horizontal (este/oeste)
	{
		if (game->raycast.ray_dir_y > 0)
			wall_color = 0x00FF00;  // Verde
		else
			wall_color = 0x008000;  // Verde oscuro
	}

	// Dibujar techo (negro)
	y = 0;
	while (y < draw_start)
	{
		img_pixel_put(&game->img, x, y, 0x000000);  // Negro para el techo
		y++;
	}

	// Dibujar pared
	y = draw_start;
	while (y <= draw_end)
	{
		img_pixel_put(&game->img, x, y, wall_color);
		y++;
	}

	// Dibujar suelo (gris oscuro)
	y = draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		img_pixel_put(&game->img, x, y, 0x404040);  // Gris oscuro para el suelo
		y++;
	}
}
