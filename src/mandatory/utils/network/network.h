/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:38 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <pthread.h>
# include <stdint.h>

# define MAX_PLAYERS 4
# define DEFAULT_PORT 8080
# define PACKET_SIZE sizeof(t_net_packet)

/* Forward declarations */
struct s_player;

/* Network packet structure for player data */
typedef struct s_net_packet
{
	uint32_t	player_id;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	uint32_t	timestamp;
}				t_net_packet;

/**
 * Remote player structure
 */
typedef struct s_remote_player
{
	uint32_t	id;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			active;
	uint32_t	last_update;
}				t_remote_player;

/**
 * Network structure
 */
typedef struct s_network
{
	int					is_server;
	int					socket_fd;
	int					client_count;
	int					client_sockets[MAX_PLAYERS];
	struct sockaddr_in	server_addr;
	pthread_t			listen_thread;
	pthread_t			send_thread;
	pthread_mutex_t		players_mutex;
	t_remote_player		remote_players[MAX_PLAYERS];
	uint32_t			my_player_id;
	int					running;
}						t_network;

/* Network functions */
int		init_network(t_network *net, int is_server, const char *ip, int port);
void	cleanup_network(t_network *net);
void	send_player_data(t_network *net, struct s_player *player);
void	update_remote_players(t_network *net);
void	*network_listen_thread(void *arg);
void	*network_send_thread(void *arg);
int		handle_new_client(t_network *net);
void	handle_client_data(t_network *net, int client_fd, t_net_packet *packet);
void	broadcast_packet(t_network *net, t_net_packet *packet, int except_fd);
t_remote_player	*get_remote_player(t_network *net, uint32_t player_id);
void	get_all_remote_players(t_network *net, t_remote_player **players, int *count);

#endif
