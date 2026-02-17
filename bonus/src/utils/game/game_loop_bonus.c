/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 16:43:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * ENGLISH: Draw a crosshair in the center of the screen.
 *
 * SPANISH: Dibuja una mira en el centro de la pantalla.
 */
static void	draw_crosshair(t_game *game)
{
	int	center_x;
	int	center_y;
	int	size;
	int	i;
	int	t;

	center_x = WIN_W / 2;
	center_y = WIN_H / 2;
	size = CROSSHAIR_SIZE;
	i = -size;
	while (i <= size)
	{
		if (i != 0)
		{
			t = (-CROSSHAIR_THICKNESS / 2) - 1;
			while (++t <= CROSSHAIR_THICKNESS / 2)
			{
				img_pixel_put(&game->img, center_x + i, center_y + t,
					CROSSHAIR_COLOR);
				img_pixel_put(&game->img, center_x + t, center_y + i,
					CROSSHAIR_COLOR);
			}
		}
		i++;
	}
}

/**
 * ENGLISH: Main render loop function called every frame.
 *          Updates movement, clears buffer, performs raycasting,
	and displays the result.
 *
 * SPANISH: Función principal del loop de render llamada cada frame.
 *          Actualiza movimiento, limpia el buffer,
	realiza raycasting y muestra el resultado.
 */

static int	render_loop(t_game *game)
{
	if (!game->mouse_captured)
		mlx_mouse_show(game->win_ptr, game->mlx_ptr);
	update_movement(game);
	enemy_update_ai(game);
	raycast(game);
	sprite_render(game);
	draw_crosshair(game);
	render_frame(game);
	render_minimap(game);
	return (0);
}

/**
 * ENGLISH: Handle window close event.
 *
 * SPANISH: Maneja el evento de cierre de ventana.
 */
static int	handle_close(t_game *game)
{
	mlx_mouse_show(game->win_ptr, game->mlx_ptr);
	clear_game(game);
	exit(0);
}

/**
 * ENGLISH: Start the main game loop with MLX event handling.
 *          Sets up keyboard events, render loop, and starts MLX loop.
 *
 * SPANISH: Inicia el loop principal del juego con manejo de eventos MLX.
 *          Configura eventos de teclado, loop de render e inicia el loop MLX.
 */
void	start_game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 4, 1L << 2, handle_mouse_press, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, render_loop, game);
	mlx_loop(game->mlx_ptr);
}
