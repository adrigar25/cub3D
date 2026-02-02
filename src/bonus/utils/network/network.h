/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 12:00:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# include "../../cub3d_bonus.h"

// Function prototypes
int		init_server_socket(t_network *net, int port);
int		init_client_socket(t_network *net, const char *ip, int port);
void		*listen_thread_func(void *arg);
void		*send_thread_func(void *arg);
void		handle_new_client(t_network *net, int client_socket);
void		broadcast_packet(t_network *net, t_net_packet *packet);
int		receive_packet(int socket_fd, t_net_packet *packet);
int		send_packet(int socket_fd, t_net_packet *packet);

#endif