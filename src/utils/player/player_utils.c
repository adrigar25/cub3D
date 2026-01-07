/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:25:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/07 15:34:08 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	int	player_count;

	i = -1;
	player_count = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				set_player_direction(&game->player, game->map[i][j]);
				player_count++;
			}
		}
	}
	if (player_count != 1)
		return (ft_error("get_player_position",
				(char *[]){"Map must have exactly one player position", NULL}),
			-1);
	return (0);
}
