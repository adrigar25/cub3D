/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	update_movement(game);
	raycast(game);
	render_frame(game);
	return (0);
}

/**
 * ENGLISH: Handle window close event.
 *
 * SPANISH: Maneja el evento de cierre de ventana.
 */
static int	handle_close(t_game *game)
{
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
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, render_loop, game);
	mlx_loop(game->mlx_ptr);
}
