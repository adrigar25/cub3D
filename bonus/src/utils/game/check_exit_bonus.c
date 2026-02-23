/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

/**
 * ENGLISH: Checks if the player is colliding with an exit tile ('A') and,
 *          if close enough, sets the game as finished and shows the cursor.
 *
 * SPANISH: Comprueba si el jugador colisiona con la casilla de salida
 *          ('A') y, si está suficientemente cerca, marca la partida como
 *          terminada y muestra el cursor.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	check_exit_collision(t_game *game)
{
	int		next_x;
	int		next_y;
	double	dx;
	double	dy;
	double	dist;

	next_x = (int)(game->player.pos_x + game->player.dir_x);
	next_y = (int)(game->player.pos_y + game->player.dir_y);
	if (next_y < 0 || next_y >= game->map.height || next_x < 0
		|| next_x >= game->map.width || !game->map.grid[next_y]
		|| game->map.grid[next_y][next_x] != 'A')
		return ;
	dx = (next_x + 0.5) - game->player.pos_x;
	dy = (next_y + 0.5) - game->player.pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 0.8 && !game->finished)
	{
		game->finished = 1;
		ft_fprintf(1, GREEN "Victory! You found the exit!\n" RESET);
		mlx_mouse_show(game->mlx_ptr, game->win_ptr);
	}
}
