/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:25:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:44:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "player.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_north_south(t_player *player, char orientation)
{
	player->dir_x = 0;
	player->plane_y = 0;
	if (orientation == 'N')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
}

static void	set_east_west(t_player *player, char orientation)
{
	player->dir_y = 0;
	player->plane_x = 0;
	if (orientation == 'E')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	else
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
}

static void	set_player_direction(t_player *player, char orientation)
{
	if (orientation == 'N' || orientation == 'S')
		set_north_south(player, orientation);
	else
		set_east_west(player, orientation);
}

int	get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.grid[++i])
	{
		j = -1;
		while (game->map.grid[i][++j])
		{
			if (is_player_char(game->map.grid[i][j]))
			{
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				set_player_direction(&game->player, game->map.grid[i][j]);
				return (0);
			}
		}
	}
	return (0);
}
