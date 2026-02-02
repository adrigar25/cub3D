/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 12:00:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.h"
#include "../../cub3d.h"
#include <sys/time.h>

/**
 * Get current timestamp in milliseconds
 */
static uint32_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * Send player data to server/clients
 */
void	send_player_data(t_network *net, t_player *player)
{
	t_net_packet	packet;
	int				i;

	if (!net->running || net->my_player_id == 0)
		return;

	packet.player_id = net->my_player_id;
	packet.pos_x = player->pos_x;
	packet.pos_y = player->pos_y;
	packet.dir_x = player->dir_x;
	packet.dir_y = player->dir_y;
	packet.plane_x = player->plane_x;
	packet.plane_y = player->plane_y;
	packet.timestamp = get_timestamp();

	if (net->is_server)
	{
		// Server: send to all clients
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (net->client_sockets[i] >= 0)
			{
				if (send(net->client_sockets[i], &packet, PACKET_SIZE, 0) < 0)
				{
					// Client disconnected
					close(net->client_sockets[i]);
					net->client_sockets[i] = -1;
					net->client_count--;
				}
			}
			i++;
		}
	}
	else
	{
		// Client: send to server
		if (send(net->socket_fd, &packet, PACKET_SIZE, 0) < 0)
		{
			ft_fprintf(2, "Failed to send data to server\n");
			net->running = 0;
		}
	}
}

/**
 * Update remote players (called from main game loop)
 */
void	update_remote_players(t_network *net)
{
	if (!net->running)
		return;

	pthread_mutex_lock(&net->players_mutex);
	
	// Here you can add interpolation logic if needed
	// For now, we just keep the data as is
	
	pthread_mutex_unlock(&net->players_mutex);
}

/**
 * Get remote player by ID
 */
t_remote_player	*get_remote_player(t_network *net, uint32_t player_id)
{
	int	i;

	if (!net->running)
		return (NULL);

	pthread_mutex_lock(&net->players_mutex);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (net->remote_players[i].active && net->remote_players[i].id == player_id)
		{
			pthread_mutex_unlock(&net->players_mutex);
			return (&net->remote_players[i]);
		}
		i++;
	}
	pthread_mutex_unlock(&net->players_mutex);
	return (NULL);
}

/**
 * Get all active remote players
 */
void	get_all_remote_players(t_network *net, t_remote_player **players, int *count)
{
	int	i;
	int	j;

	*count = 0;
	if (!net->running)
		return;

	pthread_mutex_lock(&net->players_mutex);
	i = 0;
	j = 0;
	while (i < MAX_PLAYERS && j < MAX_PLAYERS)
	{
		if (net->remote_players[i].active)
		{
			players[j] = &net->remote_players[i];
			j++;
			(*count)++;
		}
		i++;
	}
	pthread_mutex_unlock(&net->players_mutex);
}