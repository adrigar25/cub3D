/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:45:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "minimap_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "raycast_bonus.h"
#include "render_bonus.h"
#include "sprite_bonus.h"

/**
 * ENGLISH: Builds and renders the end-of-game HUD overlay, showing
 *          the round outcome and current score.
 *
 * SPANISH: Construye y renderiza el HUD de fin de partida, mostrando
 *          el resultado de la ronda y la puntuación actual.
 *
 * @param game Pointer to game structure. / Puntero a la estructura del juego.
 * @param title Title string to display. / Cadena de título a mostrar.
 * @param color Title text colour (hex). / Color del título (en hexadecimal).
 */
static void	draw_end_hud(t_game *game, const char *title, int color)
{
	char	*num;
	char	*score_line;
	t_hud	msg;

	num = ft_itoa(game->score);
	if (!num)
		return ;
	score_line = ft_strjoin("Score: ", num);
	free(num);
	if (!score_line)
		return ;
	msg.title = title;
	msg.sub = score_line;
	msg.sub2 = "Press ESC to exit.";
	msg.color = color;
	draw_hud_message(game, msg);
	free(score_line);
}

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
 *          and displays the result.
 *
 * SPANISH: Función principal del loop de render llamada cada frame.
 *          Actualiza movimiento, limpia el buffer,
 *          realiza raycasting y muestra el resultado.
 */

static int	render_loop(t_game *game)
{
	if (!game->mouse_captured)
		mlx_mouse_show(game->mlx_ptr, game->win_ptr);
	update_movement(game);
	check_collectibles(game);
	check_exit_collision(game);
	if (!game->finished)
		enemy_update_ai(game);
	raycast(game);
	sprite_render(game);
	draw_crosshair(game);
	render_minimap(game);
	render_frame(game);
	draw_score(game);
	if (game->finished == 1)
		draw_end_hud(game, "Victory!", 0x00FF55);
	else if (game->finished == 2)
		draw_end_hud(game, "GAME OVER", 0xFF4444);
	return (0);
}

/**
 * ENGLISH: Handle window close event.
 *
 * SPANISH: Maneja el evento de cierre de ventana.
 */
static int	handle_close(t_game *game)
{
	mlx_mouse_show(game->mlx_ptr, game->win_ptr);
	clear_game(game, -1);
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
