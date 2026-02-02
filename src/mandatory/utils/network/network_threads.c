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
 * Network listening thread
 */
void	*network_listen_thread(void *arg)
{
	t_network		*net;
	fd_set			read_fds;
	int				max_fd;
	int				activity;
	int				i;
	t_net_packet	packet;
	ssize_t			bytes_read;

	net = (t_network *)arg;
	
	while (net->running)
	{
		FD_ZERO(&read_fds);
		FD_SET(net->socket_fd, &read_fds);
		max_fd = net->socket_fd;

		// Add client sockets to set (server only)
		if (net->is_server)
		{
			i = 0;
			while (i < MAX_PLAYERS)
			{
				if (net->client_sockets[i] > 0)
				{
					FD_SET(net->client_sockets[i], &read_fds);
					if (net->client_sockets[i] > max_fd)
						max_fd = net->client_sockets[i];
				}
				i++;
			}
		}

		// Wait for activity on sockets (1 second timeout)
		struct timeval timeout = {1, 0};
		activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);

		if (activity < 0 || !net->running)
			break;

		// Check for new connections (server only)
		if (net->is_server && FD_ISSET(net->socket_fd, &read_fds))
		{
			handle_new_client(net);
		}

		// Check for data from existing connections
		if (net->is_server)
		{
			// Server: check all client sockets
			i = 0;
			while (i < MAX_PLAYERS)
			{
				if (net->client_sockets[i] > 0 && FD_ISSET(net->client_sockets[i], &read_fds))
				{
					bytes_read = recv(net->client_sockets[i], &packet, PACKET_SIZE, 0);
					if (bytes_read > 0)
					{
						handle_client_data(net, net->client_sockets[i], &packet);
					}
					else
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
			// Client: check server socket
			if (FD_ISSET(net->socket_fd, &read_fds))
			{
				bytes_read = recv(net->socket_fd, &packet, PACKET_SIZE, 0);
				if (bytes_read > 0)
				{
					if (net->my_player_id == 0)
					{
						// First packet contains our assigned player ID
						net->my_player_id = packet.player_id;
						ft_fprintf(1, "Received player ID: %d\n", net->my_player_id);
					}
					else
					{
						// Update remote player
						pthread_mutex_lock(&net->players_mutex);
						i = 0;
						while (i < MAX_PLAYERS)
						{
							if (net->remote_players[i].id == packet.player_id || !net->remote_players[i].active)
							{
								net->remote_players[i].id = packet.player_id;
								net->remote_players[i].pos_x = packet.pos_x;
								net->remote_players[i].pos_y = packet.pos_y;
								net->remote_players[i].dir_x = packet.dir_x;
								net->remote_players[i].dir_y = packet.dir_y;
								net->remote_players[i].plane_x = packet.plane_x;
								net->remote_players[i].plane_y = packet.plane_y;
								net->remote_players[i].last_update = get_timestamp();
								net->remote_players[i].active = 1;
								break;
							}
							i++;
						}
						pthread_mutex_unlock(&net->players_mutex);
					}
				}
				else
				{
					// Server disconnected
					ft_fprintf(1, "Disconnected from server\n");
					net->running = 0;
				}
			}
		}
	}

	return (NULL);
}

/**
 * Network sending thread (for periodic updates)
 */
void	*network_send_thread(void *arg)
{
	t_network	*net;

	net = (t_network *)arg;
	
	while (net->running)
	{
		// Sleep for 50ms (20 FPS for network updates)
		usleep(50000);
		
		// Check for inactive players (timeout after 5 seconds)
		if (net->is_server)
		{
			uint32_t current_time = get_timestamp();
			pthread_mutex_lock(&net->players_mutex);
			int i = 0;
			while (i < MAX_PLAYERS)
			{
				if (net->remote_players[i].active && 
					(current_time - net->remote_players[i].last_update) > 5000)
				{
					net->remote_players[i].active = 0;
				}
				i++;
			}
			pthread_mutex_unlock(&net->players_mutex);
		}
	}

	return (NULL);
}