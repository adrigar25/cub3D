/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_lookup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:18:08 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "sprite_bonus.h"

/**
 * ENGLISH: Searches the sprite linked list for a texture whose name
 *          starts with the given character c.
 *
 * SPANISH: Busca en la lista enlazada de sprites una textura cuyo nombre
 *          empiece por el carácter c.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param c Character to match against sprite names. /
 *          Carácter a comparar con los nombres de sprite.
 *
 * @return Pointer to the matching texture, or NULL if not found. /
 *         Puntero a la textura coincidente, o NULL si no se encuentra.
 */
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
