/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "render_bonus.h"

/**
 * ENGLISH: Handles mouse button press events. On left-click inside the
 *          window, captures the mouse and hides the cursor.
 *
 * SPANISH: Maneja los eventos de pulsación del ratón. Al hacer clic
 *          izquierdo dentro de la ventana, captura el ratón y oculta
 *          el cursor.
 *
 * @param button Mouse button code. / Código del botón del ratón.
 * @param x Cursor X position. / Posición X del cursor.
 * @param y Cursor Y position. / Posición Y del cursor.
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Always 0. / Siempre 0.
 */
int	handle_mouse_press(int button, int x, int y, t_game *game)
{
	if (button != 1 || game->mouse_captured)
		return (0);
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	game->mouse_captured = 1;
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

/**
 * ENGLISH: Handles mouse movement events. When the mouse is captured,
 *          rotates the player and adjusts pitch based on cursor delta.
 *
 * SPANISH: Maneja los eventos de movimiento del ratón. Cuando el ratón
 *          está capturado, rota al jugador y ajusta el ángulo vertical
 *          según el desplazamiento del cursor.
 *
 * @param x Current cursor X position. / Posición X actual del cursor.
 * @param y Current cursor Y position. / Posición Y actual del cursor.
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return Always 0. / Siempre 0.
 */
int	handle_mouse_move(int x, int y, t_game *game)
{
	int	center_x;
	int	center_y;
	int	delta_x;
	int	delta_y;

	if (!game->mouse_captured || game->finished)
		return (0);
	center_x = WIN_W / 2;
	center_y = WIN_H / 2;
	delta_x = x - center_x;
	delta_y = y - center_y;
	if (delta_x != 0)
		rotate_player(game, delta_x * MOUSE_SENSITIVITY);
	if (delta_y != 0)
	{
		game->player.pitch -= delta_y * 2;
		if (game->player.pitch > WIN_H / 2)
			game->player.pitch = WIN_H / 2;
		if (game->player.pitch < -WIN_H / 2)
			game->player.pitch = -WIN_H / 2;
	}
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, center_y);
	return (0);
}
