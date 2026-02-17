/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_lookup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:18:08 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite_helpers_bonus.h"

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
