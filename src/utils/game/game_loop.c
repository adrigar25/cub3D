/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 17:32:42 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * ENGLISH: Clear the image buffer by filling it with black (0x000000).
 *          Call this at the beginning of each frame.
 *
 * SPANISH: Limpia el buffer de imagen llenándolo con negro (0x000000).
 *          Llama a esto al comienzo de cada frame.
 */
static void	clear_image_buffer(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pixel_put(&game->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/**
 * ENGLISH: Main render loop function called every frame.
 *          Clears buffer, performs raycasting, and displays the result.
 *
 * SPANISH: Función principal del loop de render llamada cada frame.
 *          Limpia el buffer, realiza raycasting y muestra el resultado.
 */
static int	render_loop(t_game *game)
{
	raycast(game);
	// Mostrar el frame completo en la ventana
	render_frame(game);

	return (0);
}

/**
 * ENGLISH: Handle key press events for player movement and game controls.
 *
 * SPANISH: Maneja eventos de teclas presionadas para movimiento del jugador y controles del juego.
 */
static int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 53)  // ESC key
		exit(0);

	// Aquí puedes añadir más controles de movimiento:
	// W, A, S, D para movimiento
	// Flecha izquierda/derecha para rotación

	(void)game;  // Para evitar warning de parámetro no usado
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
	return (0);
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
	// Configurar eventos de teclado
	mlx_key_hook(game->win_ptr, handle_keypress, game);

	// Configurar evento de cierre de ventana
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);

	// Configurar el loop de render (se ejecuta continuamente)
	mlx_loop_hook(game->mlx_ptr, render_loop, game);

	// Iniciar el loop principal de MLX
	mlx_loop(game->mlx_ptr);
}
