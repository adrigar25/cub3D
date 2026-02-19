/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_list_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:30:10 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "enemy_bonus.h"
#include <stdlib.h>

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
