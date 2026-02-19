/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_lookup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:18:08 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "sprite_bonus.h"

t_texture	*sprite_get_texture(t_game *game, char c)
{
	t_texture	*cur;

	cur = game->sprites;
	while (cur)
	{
		if (cur->name && cur->name[0] == c)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
