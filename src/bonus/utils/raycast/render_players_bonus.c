/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

/**
 * ENGLISH: Converts world coordinates to screen coordinates
 *
 * SPANISH: Convierte coordenadas del mundo a coordenadas de pantalla
 */
static void	world_to_screen(t_game *game, double world_x, double world_y,
				int *screen_x, int *screen_y)
{
	double	rel_x = world_x - game->player.pos_x;
	double	rel_y = world_y - game->player.pos_y;
	double	angle = atan2(rel_y, rel_x);
	double	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	double	relative_angle = angle - player_angle;

	while (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	while (relative_angle < -M_PI)
		relative_angle += 2 * M_PI;

	if (fabs(relative_angle) > M_PI / 3)
	{
		*screen_x = -1;
		*screen_y = -1;
		return;
	}

	*screen_x = WIN_W / 2 + (int)(tan(relative_angle) * WIN_W / 2);
	*screen_y = WIN_H / 2;
}

/**
 * ENGLISH: Draw a simple player sprite on screen
 *
 * SPANISH: Dibuja un sprite simple de jugador en pantalla
 */
static void	draw_player_sprite(t_game *game, int screen_x, int screen_y, int player_id)
{
	int		size = 8;
	int		color = 0xFF0000 + (player_id * 0x001100);
	int		x, y;

	if (screen_x < 0 || screen_y < 0 || screen_x >= WIN_W || screen_y >= WIN_H)
		return;

	for (y = -size; y <= size; y++)
	{
		for (x = -size; x <= size; x++)
		{
			if (x * x + y * y <= size * size)
			{
				if (screen_x + x >= 0 && screen_x + x < WIN_W &&
					screen_y + y >= 0 && screen_y + y < WIN_H)
				{
					img_pixel_put(&game->img, screen_x + x,
						screen_y + y, color);
				}
			}
		}
	}
}

/**
 * ENGLISH: Render all remote players on the screen
 *
 * SPANISH: Renderiza todos los jugadores remotos en pantalla
 */
void	render_network_players(t_game *game)
{
	int	i;
	int	screen_x, screen_y;

	if (!game->network || !game->network->running)
		return;

	// Render remote players from network
	for (i = 0; i < MAX_CLIENTS; i++)
	{
		if (game->network->remote_players[i] &&
			i != game->network->my_player_id)
		{
			world_to_screen(game,
				game->network->remote_players[i]->pos_x,
				game->network->remote_players[i]->pos_y,
				&screen_x, &screen_y);

			if (screen_x >= 0 && screen_y >= 0)
			{
				draw_player_sprite(game, screen_x, screen_y, i);
			}
		}
	}
}

/**
 * ENGLISH: Draw network status information on screen
 *
 * SPANISH: Dibuja información del estado de red en pantalla
 */
void	draw_network_status(t_game *game)
{
	char	buffer[256];
	int		y_offset = 30;

	if (!game->network)
		return;

	if (game->network->is_server)
	{
		snprintf(buffer, sizeof(buffer), "Server: %d clients connected",
			game->network->client_count);
	}
	else
	{
		snprintf(buffer, sizeof(buffer), "Client: Player ID %d",
			game->network->my_player_id);
	}

	// This would require a text rendering function
	// For now, we'll skip text rendering as it's not implemented in the base cub3d
	(void)buffer;
	(void)y_offset;
}
