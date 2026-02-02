/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.h"

/**
 * Initialize network structure
 */
static void	init_network_struct(t_network *net)
{
	int	i;

	net->server_socket = -1;
	net->client_count = 0;
	net->my_player_id = 0;
	net->running = 1;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		net->client_sockets[i] = -1;
		net->remote_players[i] = NULL;
		i++;
	}
}

/**
 * Initialize server socket
 */
int	init_server_socket(t_network *net, int port)
{
	int	opt = 1;

	net->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (net->server_socket < 0)
	{
		printf("Error: Failed to create socket\n");
		return (-1);
	}
	if (setsockopt(net->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		printf("Error: Failed to set socket options\n");
		return (-1);
	}
	net->server_addr.sin_family = AF_INET;
	net->server_addr.sin_addr.s_addr = INADDR_ANY;
	net->server_addr.sin_port = htons(port);
	if (bind(net->server_socket, (struct sockaddr*)&net->server_addr, sizeof(net->server_addr)) < 0)
	{
		printf("Error: Failed to bind socket\n");
		return (-1);
	}
	if (listen(net->server_socket, MAX_CLIENTS) < 0)
	{
		printf("Error: Failed to listen on socket\n");
		return (-1);
	}
	printf("Server listening on port %d\n", port);
	return (0);
}

/**
 * Initialize client socket
 */
int	init_client_socket(t_network *net, const char *ip, int port)
{
	net->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (net->server_socket < 0)
	{
		printf("Error: Failed to create socket\n");
		return (-1);
	}
	net->server_addr.sin_family = AF_INET;
	net->server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &net->server_addr.sin_addr) <= 0)
	{
		printf("Error: Invalid IP address\n");
		return (-1);
	}
	if (connect(net->server_socket, (struct sockaddr*)&net->server_addr, sizeof(net->server_addr)) < 0)
	{
		printf("Error: Failed to connect to server\n");
		return (-1);
	}
	printf("Connected to server at %s:%d\n", ip, port);
	return (0);
}

/**
 * Initialize network system
 */
int	init_network(t_game *game, int is_server, const char *ip, int port)
{
	t_network	*net;

	net = malloc(sizeof(t_network));
	if (!net)
		return (-1);
	init_network_struct(net);
	net->is_server = is_server;
	if (is_server)
	{
		if (init_server_socket(net, port) < 0)
		{
			free(net);
			return (-1);
		}
		net->my_player_id = 1;
	}
	else
	{
		if (init_client_socket(net, ip, port) < 0)
		{
			free(net);
			return (-1);
		}
	}
	game->network = net;
	return (0);
}

/**
 * Cleanup network resources
 */
void	cleanup_network(t_game *game)
{
	t_network	*net;
	int			i;

	if (!game || !game->network)
		return;
	net = game->network;
	net->running = 0;
	if (net->server_socket >= 0)
		close(net->server_socket);
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (net->client_sockets[i] >= 0)
			close(net->client_sockets[i]);
		i++;
	}
	free(net);
	game->network = NULL;
}
