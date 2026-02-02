/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.h"

/**
 * Listen thread function (simplified)
 */
void	*listen_thread_func(void *arg)
{
	(void)arg;
	return (NULL);
}

/**
 * Send thread function (simplified)
 */
void	*send_thread_func(void *arg)
{
	(void)arg;
	return (NULL);
}

/**
 * Handle new client (simplified)
 */
void	handle_new_client(t_network *net, int client_socket)
{
	int					i;
	struct sockaddr_in	addr;
	socklen_t			addr_len;
	char				ip_str[INET_ADDRSTRLEN];
	t_net_packet		packet;

	// Get client IP address
	addr_len = sizeof(addr);
	if (getpeername(client_socket, (struct sockaddr *)&addr, &addr_len) == 0)
	{
		inet_ntop(AF_INET, &addr.sin_addr, ip_str, INET_ADDRSTRLEN);
	}
	else
	{
		ft_strlcpy(ip_str, "unknown", INET_ADDRSTRLEN);
	}

	i = 0;
	while (i < MAX_CLIENTS && net->client_sockets[i] >= 0)
		i++;
	if (i < MAX_CLIENTS)
	{
		net->client_sockets[i] = client_socket;
		net->client_count++;
		printf(GREEN "🌐 New client connected from %s\n" RESET, ip_str);
		printf(GREEN "   Total clients: %d\n" RESET, net->client_count);
		
		// Send map info to new client
		packet.type = PACKET_MAP_INFO;
		packet.player_id = net->my_player_id;
		ft_strlcpy(packet.map_name, net->map_name, 256);
		send_packet(client_socket, &packet);
	}
	else
	{
		printf(RED "❌ Max clients reached, rejecting connection from %s\n" RESET, ip_str);
		close(client_socket);
	}
}

/**
 * Broadcast packet to all clients
 */
void	broadcast_packet(t_network *net, t_net_packet *packet)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (net->client_sockets[i] >= 0)
			send_packet(net->client_sockets[i], packet);
		i++;
	}
}
