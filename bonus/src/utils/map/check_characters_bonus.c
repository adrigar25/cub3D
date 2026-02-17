/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 01:02:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_allowed_char(t_game *game, char c)
{
	t_texture	*cur;

	if (ft_strchr(" 01NSEWD\n", c))
		return (1);
	if (game)
		cur = game->sprites;
	else
		cur = NULL;
	while (cur)
	{
		if (cur->name && cur->name[0] == c)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	check_valid_characters(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map)
		return (-1);
	i = -1;
	while (game->map[++i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_allowed_char(game, game->map[i][j]))
				return (-1);
			j++;
		}
	}
	return (0);
}
