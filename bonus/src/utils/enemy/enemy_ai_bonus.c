/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:30 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy_bonus.h"
#include "game_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include <math.h>

/**
 * ENGLISH: Moves the enemy towards the player if it has line-of-sight
 *          and is within aggro range. Triggers game-over on contact.
 *
 * SPANISH: Mueve al enemigo hacia el jugador si tiene línea de visión
 *          y está dentro del rango de agro. Activa game-over al contacto.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param e Pointer to the enemy to move. /
 *           Puntero al enemigo a mover.
 */
static void	enemy_try_move(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;
	double	dist;
	double	scale;

	dx = game->player.pos_x - e->x;
	dy = game->player.pos_y - e->y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.0001 && dist <= ENEMY_AGGRO_RANGE_TILES
		&& enemy_can_see_player(game, e))
	{
		scale = ENEMY_SPEED / dist;
		dx *= scale;
		dy *= scale;
		if (is_valid_position(game, e->x + dx, e->y))
			e->x += dx;
		if (is_valid_position(game, e->x, e->y + dy))
			e->y += dy;
		if (dist < 0.5)
		{
			game->finished = 2;
			mlx_mouse_show(game->mlx_ptr, game->win_ptr);
			return ;
		}
	}
}

/**
 * ENGLISH: Updates the enemy animation state based on whether it moved
 *          since the last frame.
 *
 * SPANISH: Actualiza el estado de animación del enemigo en función de si
 *          se movió desde el último frame.
 *
 * @param e Pointer to the enemy. / Puntero al enemigo.
 * @param prev_x Previous X position. / Posición X anterior.
 * @param prev_y Previous Y position. / Posición Y anterior.
 */
static void	enemy_update_anim(t_enemy *e, double prev_x, double prev_y)
{
	if (fabs(e->x - prev_x) + fabs(e->y - prev_y) > 1e-5)
	{
		e->moving = 1;
		e->anim_timer++;
		if (e->anim_timer >= ENEMY_ANIM_SPEED_FRAMES)
		{
			e->anim_timer = 0;
			e->anim_frame ^= 1;
		}
	}
	else
	{
		e->moving = 0;
		e->anim_timer = 0;
		e->anim_frame = 0;
	}
	e->last_x = e->x;
	e->last_y = e->y;
}

/**
 * ENGLISH: Iterates over all enemies, moves each one towards the player
 *          and updates their animation state.
 *
 * SPANISH: Itera sobre todos los enemigos, mueve cada uno hacia el jugador
 *          y actualiza su estado de animación.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
void	enemy_update_ai(t_game *game)
{
	t_enemy	*e;
	double	prev_x;
	double	prev_y;

	if (!game)
		return ;
	e = game->enemies;
	while (e)
	{
		prev_x = e->x;
		prev_y = e->y;
		enemy_try_move(game, e);
		enemy_update_anim(e, prev_x, prev_y);
		e = e->next;
	}
}
