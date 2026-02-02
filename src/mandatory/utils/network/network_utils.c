/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:38 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * Initialize network for the game
 */
int	init_game_network(t_game *game, int is_server, const char *ip, int port)
{
	if (init_network(&game->network, is_server, ip, port))
		return (1);
	return (0);
}

/**
 * Update network (send player data and update remote players)
 */
void	update_network(t_game *game)
{
	static int	update_counter = 0;

	// Send player data every 3 frames (20 FPS at 60 FPS game loop)
	update_counter++;
	if (update_counter >= 3)
	{
		send_player_data(&game->network, &game->player);
		update_counter = 0;
	}

	// Update remote players data
	update_remote_players(&game->network);
}

/**
 * Cleanup network resources
 */
void	cleanup_game_network(t_game *game)
{
	cleanup_network(&game->network);
}
