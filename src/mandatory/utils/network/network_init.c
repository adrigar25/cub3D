/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:38 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.h"
#include "../../cub3d.h"

/**
 * Initialize network structure
 */
static void	init_network_struct(t_network *net)
{
	int	i;

	net->socket_fd = -1;
	net->client_count = 0;
	net->my_player_id = 0;
	net->running = 1;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		net->client_sockets[i] = -1;
		net->remote_players[i].active = 0;
		net->remote_players[i].id = 0;
		i++;
	}
	pthread_mutex_init(&net->players_mutex, NULL);
}

/**
 * Initialize server socket
 */
static int	init_server_socket(t_network *net, int port)
{
	int	opt = 1;

	net->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (net->socket_fd < 0)
		return (ft_fprintf(2, "Error: Failed to create socket\n"), 1);
	if (setsockopt(net->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		return (ft_fprintf(2, "Error: Failed to set socket options\n"), 1);

	net->server_addr.sin_family = AF_INET;
	net->server_addr.sin_addr.s_addr = INADDR_ANY;
	net->server_addr.sin_port = htons(port);

	if (bind(net->socket_fd, (struct sockaddr*)&net->server_addr, sizeof(net->server_addr)) < 0)
		return (ft_fprintf(2, "Error: Failed to bind socket\n"), 1);

	if (listen(net->socket_fd, MAX_PLAYERS) < 0)
		return (ft_fprintf(2, "Error: Failed to listen on socket\n"), 1);

	ft_fprintf(1, "Server listening on port %d\n", port);
	return (0);
}

/**
 * Initialize client socket
 */
static int	init_client_socket(t_network *net, const char *ip, int port)
{
	net->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (net->socket_fd < 0)
		return (ft_fprintf(2, "Error: Failed to create socket\n"), 1);

	net->server_addr.sin_family = AF_INET;
	net->server_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip, &net->server_addr.sin_addr) <= 0)
		return (ft_fprintf(2, "Error: Invalid IP address\n"), 1);

	if (connect(net->socket_fd, (struct sockaddr*)&net->server_addr, sizeof(net->server_addr)) < 0)
		return (ft_fprintf(2, "Error: Failed to connect to server\n"), 1);

	ft_fprintf(1, "Connected to server at %s:%d\n", ip, port);
	return (0);
}

/**
 * Initialize network system
 */
int	init_network(t_network *net, int is_server, const char *ip, int port)
{
	init_network_struct(net);
	net->is_server = is_server;

	if (is_server)
	{
		if (init_server_socket(net, port))
			return (1);
		net->my_player_id = 1; // Server is always player 1
	}
	else
	{
		if (init_client_socket(net, ip, port))
			return (1);
		// Client ID will be assigned by server
	}

	// Create network threads
	if (pthread_create(&net->listen_thread, NULL, network_listen_thread, net) != 0)
		return (ft_fprintf(2, "Error: Failed to create listen thread\n"), 1);

	if (pthread_create(&net->send_thread, NULL, network_send_thread, net) != 0)
		return (ft_fprintf(2, "Error: Failed to create send thread\n"), 1);

	return (0);
}

/**
 * Cleanup network resources
 */
void	cleanup_network(t_network *net)
{
	int	i;

	net->running = 0;

	// Join threads
	if (net->listen_thread)
		pthread_join(net->listen_thread, NULL);
	if (net->send_thread)
		pthread_join(net->send_thread, NULL);

	// Close sockets
	if (net->socket_fd >= 0)
		close(net->socket_fd);

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (net->client_sockets[i] >= 0)
			close(net->client_sockets[i]);
		i++;
	}

	pthread_mutex_destroy(&net->players_mutex);
}
