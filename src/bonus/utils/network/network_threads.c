/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 12:00:00 by agarcia          ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < MAX_CLIENTS && net->client_sockets[i] >= 0)
		i++;
	if (i < MAX_CLIENTS)
	{
		net->client_sockets[i] = client_socket;
		net->client_count++;
		printf("New client connected. Total clients: %d\n", net->client_count);
	}
	else
	{
		printf("Max clients reached, rejecting connection\n");
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