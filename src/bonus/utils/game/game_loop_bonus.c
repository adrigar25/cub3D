/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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
// Limita el bucle a FPS_TARGET usando gettimeofday/usleep
#include <sys/time.h>

static int	render_loop(t_game *game)
{
	if (game->menu.state == MENU_MAIN)
	{
		render_menu(game);
		return (0);
	}
	else if (game->menu.state == MENU_MULTIPLAYER)
	{
		render_multiplayer_menu(game);
		return (0);
	}
	else if (game->menu.state == MENU_MAP_SELECTION)
	{
		render_map_selection_menu(game);
		return (0);
	}
	else if (game->menu.state == MENU_ENTER_IP)
	{
		render_enter_ip_menu(game);
		return (0);
	}

	if (game->menu.state == GAME_RUNNING)
	{
		update_movement(game);

		// Handle networking if enabled
		if (game->network && game->network->running)
		{
			handle_network_packets(game);
			broadcast_player_state(game);
			update_remote_players(game);
		}

		raycast(game);

		// Render remote players if networking is enabled
		if (game->network && game->network->running)
			render_network_players(game);

		draw_crosshair(game);
		render_frame(game);
		print_minimap(game);
	}

	return (0);
}

/**
 * ENGLISH: Handle window close event.
 *
 * SPANISH: Maneja el evento de cierre de ventana.
 */
static int	handle_close(t_game *game)
{
	mlx_mouse_show();
	if (game->network)
		cleanup_network(game);
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
	init_keys(game);
	mlx_mouse_hide();
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, render_loop, game);
	mlx_loop(game->mlx_ptr);
}
