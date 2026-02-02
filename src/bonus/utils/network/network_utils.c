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
	packet.type = PACKET_PLAYER_UPDATE;
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
 * Process received packet
 */
static void	process_packet(t_game *game, t_net_packet *packet)
{
	if (packet->type == PACKET_DOOR_TOGGLE)
	{
		// Apply door toggle to map
		if (packet->door_y >= 0 && packet->door_y < game->map_h &&
			packet->door_x >= 0 && packet->door_x < game->map_w)
		{
			if (game->map[packet->door_y][packet->door_x] == 'D')
				game->map[packet->door_y][packet->door_x] = '0';
		}
	}
	else if (packet->type == PACKET_PLAYER_UPDATE)
	{
		// TODO: Update remote player position
		(void)game;
	}
}

/**
 * Handle incoming network packets
 */
void	handle_network_packets(t_game *game)
{
	t_network			*net;
	int					new_socket;
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;
	fd_set				read_fds;
	struct timeval		timeout;
	t_net_packet		packet;
	int					i;
	int					max_fd;

	if (!game || !game->network)
		return;
	
	net = game->network;
	
	// If server, check for new connections
	if (net->is_server && net->server_socket >= 0)
	{
		FD_ZERO(&read_fds);
		FD_SET(net->server_socket, &read_fds);
		max_fd = net->server_socket;
		
		// Add all client sockets to the set
		i = 0;
		while (i < MAX_CLIENTS)
		{
			if (net->client_sockets[i] >= 0)
			{
				FD_SET(net->client_sockets[i], &read_fds);
				if (net->client_sockets[i] > max_fd)
					max_fd = net->client_sockets[i];
			}
			i++;
		}
		
		// Non-blocking check
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		
		if (select(max_fd + 1, &read_fds, NULL, NULL, &timeout) > 0)
		{
			// Check for new connections
			if (FD_ISSET(net->server_socket, &read_fds))
			{
				addr_len = sizeof(client_addr);
				new_socket = accept(net->server_socket, 
					(struct sockaddr *)&client_addr, &addr_len);
				
				if (new_socket >= 0)
					handle_new_client(net, new_socket);
			}
			
			// Check for data from existing clients
			i = 0;
			while (i < MAX_CLIENTS)
			{
				if (net->client_sockets[i] >= 0 && 
					FD_ISSET(net->client_sockets[i], &read_fds))
				{
					if (receive_packet(net->client_sockets[i], &packet) == 0)
					{
						process_packet(game, &packet);
						// Broadcast to other clients
						broadcast_packet(net, &packet);
					}
				}
				i++;
			}
		}
	}
	else if (!net->is_server && net->server_socket >= 0)
	{
		// Client: check for data from server
		FD_ZERO(&read_fds);
		FD_SET(net->server_socket, &read_fds);
		
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		
		if (select(net->server_socket + 1, &read_fds, NULL, NULL, &timeout) > 0)
		{
			if (FD_ISSET(net->server_socket, &read_fds))
			{
				if (receive_packet(net->server_socket, &packet) == 0)
					process_packet(game, &packet);
			}
		}
	}
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
