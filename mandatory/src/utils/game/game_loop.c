/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "game.h"
#include "player.h"
#include "raycast.h"
#include "render.h"
#include <stdlib.h>

/**
 * ENGLISH: Main render loop callback called every frame. Updates player
 * 			movement, performs raycasting and pushes the frame to screen.
 *
 * SPANISH: Callback principal del loop llamado cada frame. Actualiza el
 * 			movimiento del jugador, realiza el raycasting y muestra el frame.
 *
 * @param game Pointer to the game structure. / Puntero al juego.
 *
 * @return Always 0. / Siempre 0.
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
 *
 * @param game Pointer to the game structure. / Puntero al juego.
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
 *
 * @param game Pointer to the initialized game structure. / Puntero a la
 *             estructura del juego inicializada.
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
