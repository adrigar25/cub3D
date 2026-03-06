/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_vision_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:20:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

/**
 * ENGLISH: Returns 1 if the map cell (mx, my) blocks line-of-sight
 *          (wall, door, or exit tile). Returns 1 also for out-of-bounds.
 *
 * SPANISH: Retorna 1 si la celda (mx, my) bloquea la línea de visión
 *          (pared, puerta o salida). Retorna 1 también si está fuera
 *          de límites.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param mx Map cell column. / Columna de la celda del mapa.
 * @param my Map cell row. / Fila de la celda del mapa.
 *
 * @return 1 if blocking, 0 if passable. / 1 si bloquea, 0 si transitable.
 */
static int	is_blocking_tile(t_game *game, int mx, int my)
{
	char	c;

	if (my < 0 || my >= game->map.height || mx < 0)
		return (1);
	if (!game->map.grid[my])
		return (1);
	if (mx >= (int)ft_strlen(game->map.grid[my]))
		return (1);
	c = game->map.grid[my][mx];
	return (c == '1' || c == 'D' || c == 'A');
}

/**
 * ENGLISH: Checks a single LOS step at float position (x, y).
 *
 * SPANISH: Comprueba un paso individual de la línea de visión en la
 *          posición flotante (x, y).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x Float X coordinate to check. / Coordenada X flotante a revisar.
 * @param y Float Y coordinate to check. / Coordenada Y flotante a revisar.
 *
 * @return 1 if the cell is passable, 0 if blocked. /
 *         1 si la celda es transitable, 0 si está bloqueada.
 */
static int	check_los_step(t_game *game, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (is_blocking_tile(game, mx, my))
		return (0);
	return (1);
}

/**
 * ENGLISH: Traces a ray from (x0,y0) to the enemy position in 0.1-unit
 *          steps, returning 1 if no blocking tile is found in between.
 *
 * SPANISH: Traza un rayo desde (x0,y0) hasta la posición del enemigo
 *          en pasos de 0.1 unidades, retornando 1 si no hay casilla
 *          bloqueante entre medias.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param x0 Start X position. / Posición X de inicio.
 * @param y0 Start Y position. / Posición Y de inicio.
 * @param e Pointer to the target enemy. / Puntero al enemigo destino.
 *
 * @return 1 if clear LOS, 0 if blocked. /
 *         1 si la visión es despejada, 0 si está bloqueada.
 */
static int	has_clear_los(t_game *game, double x0, double y0, t_enemy *e)
{
	double	dx;
	double	dy;
	double	dist;
	int		steps;
	int		i;

	dx = e->x - x0;
	dy = e->y - y0;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 1e-6)
		return (1);
	steps = (int)(dist / 0.1);
	i = 1;
	while (i <= steps)
	{
		if (!check_los_step(game, x0 + (dx / dist) * (i * 0.1), y0 + (dy / dist)
				* (i * 0.1)))
			return (0);
		i++;
	}
	return (1);
}

/**
 * ENGLISH: Checks whether an enemy has a clear line of sight to the
 *          player and is within aggro range.
 *
 * SPANISH: Comprueba si un enemigo tiene línea de visión despejada
 *          hacia el jugador y está dentro del rango de agro.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param e Pointer to the enemy. / Puntero al enemigo.
 *
 * @return 1 if the enemy can see the player, 0 otherwise. /
 *         1 si el enemigo puede ver al jugador, 0 en caso contrario.
 */
int	enemy_can_see_player(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;
	double	dist;

	if (!game || !e)
		return (0);
	dx = e->x - game->player.pos_x;
	dy = e->y - game->player.pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > ENEMY_AGGRO_RANGE_TILES)
		return (0);
	if (!has_clear_los(game, game->player.pos_x, game->player.pos_y, e))
		return (0);
	return (1);
}
