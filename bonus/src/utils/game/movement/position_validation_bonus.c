/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_validation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "player_bonus.h"

/**
 * ENGLISH: Checks if the position (x, y) is walkable, i.e. none of the
 *          four hitbox corners collide with a wall, door or exit tile.
 *
 * SPANISH: Comprueba si la posición (x, y) es transitable, es decir que
 *          ninguna de las cuatro esquinas del hitbox colisiona con pared,
 *          puerta o casilla de salida.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x X position to validate. / Posición X a validar.
 * @param y Y position to validate. / Posición Y a validar.
 *
 * @return 1 if the position is valid, 0 otherwise. /
 *         1 si la posición es válida, 0 en caso contrario.
 */
int	is_valid_position(t_game *game, double x, double y)
{
	double	margin;
	int		map_x;
	int		map_y;

	margin = PLAYER_HITBOX;
	if (ft_strchr("1DA", game->map.grid[(int)(y - margin)][(int)(x - margin)]))
		return (0);
	if (ft_strchr("1DA", game->map.grid[(int)(y - margin)][(int)(x + margin)]))
		return (0);
	if (ft_strchr("1DA", game->map.grid[(int)(y + margin)][(int)(x - margin)]))
		return (0);
	if (ft_strchr("1DA", game->map.grid[(int)(y + margin)][(int)(x + margin)]))
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (0);
	if (!game->map.grid[map_y] || !game->map.grid[map_y][map_x])
		return (0);
	if (ft_strchr("1DA", game->map.grid[map_y][map_x]))
		return (0);
	return (1);
}
