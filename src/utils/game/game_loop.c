/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 18:46:07 by adriescr         ###   ########.fr       */
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
 *          Updates movement, clears buffer, performs raycasting, and displays the result.
 *
 * SPANISH: Función principal del loop de render llamada cada frame.
 *          Actualiza movimiento, limpia el buffer, realiza raycasting y muestra el resultado.
 */
static int	render_loop(t_game *game)
{
	// Actualizar movimiento basado en teclas presionadas
	update_movement(game);

	// Realizar raycasting y renderizar
	raycast(game);

	// Mostrar el frame completo en la ventana
	render_frame(game);

	return (0);
}

/**
 * ENGLISH: Initialize all key states to 0 (not pressed).
 *
 * SPANISH: Inicializa todos los estados de teclas a 0 (no presionadas).
 */
void	init_keys(t_game *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.up = 0;
	game->keys.down = 0;
}

/**
 * ENGLISH: Handle key press events - set key state to 1.
 *
 * SPANISH: Maneja eventos de teclas presionadas - establece el estado de la tecla a 1.
 */
static int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_UP)
		game->keys.up = 1;
	else if (keycode == KEY_DOWN)
		game->keys.down = 1;
	return (0);
}

/**
 * ENGLISH: Handle key release events - set key state to 0.
 *
 * SPANISH: Maneja eventos de teclas liberadas - establece el estado de la tecla a 0.
 */
static int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	else if (keycode == KEY_UP)
		game->keys.up = 0;
	else if (keycode == KEY_DOWN)
		game->keys.down = 0;
	return (0);
}

/**
 * ENGLISH: Update player movement based on current key states.
 *
 * SPANISH: Actualiza el movimiento del jugador basado en los estados actuales de las teclas.
 */
void	update_movement(t_game *game)
{
	if (game->keys.w || game->keys.up)
		move_forward(game);
	if (game->keys.s || game->keys.down)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
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
	// Inicializar estados de teclas
	init_keys(game);

	// Configurar eventos de teclado (presionar y soltar)
	mlx_hook(game->win_ptr, 2, 1L<<0, handle_keypress, game);    // KeyPress
	mlx_hook(game->win_ptr, 3, 1L<<1, handle_keyrelease, game);  // KeyRelease

	// Configurar evento de cierre de ventana
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);

	// Configurar el loop de render (se ejecuta continuamente)
	mlx_loop_hook(game->mlx_ptr, render_loop, game);

	// Iniciar el loop principal de MLX
	mlx_loop(game->mlx_ptr);
}
