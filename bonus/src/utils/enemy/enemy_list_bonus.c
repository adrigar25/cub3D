/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_list_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:10 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "enemy_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Appends an enemy node to the end of the game's enemy linked list.
 *
 * SPANISH: Añade un nodo de enemigo al final de la lista enlazada de
 *          enemigos del juego.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param node Pointer to the enemy node to add. /
 *             Puntero al nodo de enemigo a añadir.
 */
void	enemy_add(t_game *game, t_enemy *node)
{
	t_enemy	*it;

	if (!game || !node)
		return ;
	if (!game->enemies)
	{
		game->enemies = node;
		return ;
	}
	it = game->enemies;
	while (it->next)
		it = it->next;
	it->next = node;
}

/**
 * ENGLISH: Frees all nodes in an enemy linked list and sets the pointer
 *          to NULL.
 *
 * SPANISH: Libera todos los nodos de una lista enlazada de enemigos y
 *          establece el puntero a NULL.
 *
 * @param list Pointer to the head pointer of the enemy list. /
 *             Puntero al puntero de cabeza de la lista de enemigos.
 */
void	enemy_clear(t_enemy **list)
{
	t_enemy	*it;
	t_enemy	*n;

	if (!list || !*list)
		return ;
	it = *list;
	while (it)
	{
		n = it->next;
		free(it);
		it = n;
	}
	*list = NULL;
}
