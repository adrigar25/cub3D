/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.h"

/**
 * Send player data over network
 */
void	broadcast_player_state(t_game *game)
{
	t_net_packet	packet;
	t_network		*net;
	int				i;

	if (!game || !game->network)
		return;
	net = game->network;
	packet.type = 1;
	packet.player_id = net->my_player_id;
	packet.pos_x = game->player.pos_x;
	packet.pos_y = game->player.pos_y;
	packet.dir_x = game->player.dir_x;
	packet.dir_y = game->player.dir_y;
	packet.plane_x = game->player.plane_x;
	packet.plane_y = game->player.plane_y;
	if (net->is_server)
	{
		i = 0;
		while (i < MAX_CLIENTS)
		{
			if (net->client_sockets[i] >= 0)
				send_packet(net->client_sockets[i], &packet);
			i++;
		}
	}
	else
	{
		send_packet(net->server_socket, &packet);
	}
}

/**
 * Send a packet to a socket
 */
int	send_packet(int socket_fd, t_net_packet *packet)
{
	ssize_t	bytes_sent;

	bytes_sent = send(socket_fd, packet, sizeof(t_net_packet), 0);
	if (bytes_sent != sizeof(t_net_packet))
		return (-1);
	return (0);
}

/**
 * Receive a packet from a socket
 */
int	receive_packet(int socket_fd, t_net_packet *packet)
{
	ssize_t	bytes_received;

	bytes_received = recv(socket_fd, packet, sizeof(t_net_packet), 0);
	if (bytes_received != sizeof(t_net_packet))
		return (-1);
	return (0);
}

/**
 * Handle incoming network packets
 */
void	handle_network_packets(t_game *game)
{
	(void)game;
	// Simplified version - no actual packet handling for basic integration
}

/**
 * Update remote players
 */
void	update_remote_players(t_game *game)
{
	(void)game;
	// Simplified version - no actual remote players for basic integration
}

/**
 * Render network players
 */
