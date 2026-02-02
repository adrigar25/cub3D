/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_server.c                                   :+:      :+:    :+:   */
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
 * Handle new client connection
 */
int	handle_new_client(t_network *net)
{
	int					client_fd;
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;
	int					i;
	t_net_packet		welcome_packet;

	addr_len = sizeof(client_addr);
	client_fd = accept(net->socket_fd, (struct sockaddr*)&client_addr, &addr_len);
	if (client_fd < 0)
		return (1);

	// Find empty slot for client
	i = 0;
	while (i < MAX_PLAYERS && net->client_sockets[i] >= 0)
		i++;
	
	if (i >= MAX_PLAYERS)
	{
		ft_fprintf(1, "Server full, rejecting client\n");
		close(client_fd);
		return (1);
	}

	net->client_sockets[i] = client_fd;
	net->client_count++;

	// Send welcome packet with assigned player ID
	welcome_packet.player_id = i + 2; // Server is 1, clients start from 2
	welcome_packet.pos_x = 0;
	welcome_packet.pos_y = 0;
	welcome_packet.dir_x = 0;
	welcome_packet.dir_y = 0;
	welcome_packet.plane_x = 0;
	welcome_packet.plane_y = 0;
	welcome_packet.timestamp = get_timestamp();

	send(client_fd, &welcome_packet, PACKET_SIZE, 0);

	ft_fprintf(1, "Client connected, assigned ID: %d\n", welcome_packet.player_id);

	return (0);
}

/**
 * Handle client data packet
 */
void	handle_client_data(t_network *net, int client_fd, t_net_packet *packet)
{
	int	i;

	pthread_mutex_lock(&net->players_mutex);

	// Update remote player data
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (net->remote_players[i].id == packet->player_id)
		{
			net->remote_players[i].pos_x = packet->pos_x;
			net->remote_players[i].pos_y = packet->pos_y;
			net->remote_players[i].dir_x = packet->dir_x;
			net->remote_players[i].dir_y = packet->dir_y;
			net->remote_players[i].plane_x = packet->plane_x;
			net->remote_players[i].plane_y = packet->plane_y;
			net->remote_players[i].last_update = get_timestamp();
			net->remote_players[i].active = 1;
			break;
		}
		i++;
	}

	// If player not found, add new player
	if (i >= MAX_PLAYERS)
	{
		i = 0;
		while (i < MAX_PLAYERS && net->remote_players[i].active)
			i++;
		if (i < MAX_PLAYERS)
		{
			net->remote_players[i].id = packet->player_id;
			net->remote_players[i].pos_x = packet->pos_x;
			net->remote_players[i].pos_y = packet->pos_y;
			net->remote_players[i].dir_x = packet->dir_x;
			net->remote_players[i].dir_y = packet->dir_y;
			net->remote_players[i].plane_x = packet->plane_x;
			net->remote_players[i].plane_y = packet->plane_y;
			net->remote_players[i].last_update = get_timestamp();
			net->remote_players[i].active = 1;
		}
	}

	pthread_mutex_unlock(&net->players_mutex);

	// Broadcast to all other clients
	broadcast_packet(net, packet, client_fd);
}

/**
 * Broadcast packet to all clients except sender
 */
void	broadcast_packet(t_network *net, t_net_packet *packet, int except_fd)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (net->client_sockets[i] >= 0 && net->client_sockets[i] != except_fd)
		{
			if (send(net->client_sockets[i], packet, PACKET_SIZE, 0) < 0)
			{
				// Client disconnected
				close(net->client_sockets[i]);
				net->client_sockets[i] = -1;
				net->client_count--;
				
				// Mark remote player as inactive
				pthread_mutex_lock(&net->players_mutex);
				int j = 0;
				while (j < MAX_PLAYERS)
				{
					if (net->remote_players[j].id == packet->player_id)
					{
						net->remote_players[j].active = 0;
						break;
					}
					j++;
				}
				pthread_mutex_unlock(&net->players_mutex);
			}
		}
		i++;
	}
}