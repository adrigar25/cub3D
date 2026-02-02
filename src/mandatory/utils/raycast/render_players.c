/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:38 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * Transform world coordinates to screen coordinates
 */
static void	world_to_screen(t_game *game, double world_x, double world_y, int *screen_x, int *screen_y)
{
	double	rel_x, rel_y;
	double	transformed_x, transformed_y;
	double	depth;

	// Calculate relative position to player
	rel_x = world_x - game->player.pos_x;
	rel_y = world_y - game->player.pos_y;

	// Transform coordinates using camera matrix (inverse of player direction)
	transformed_x = rel_y * game->player.dir_x - rel_x * game->player.dir_y;
	transformed_y = rel_x * game->player.dir_x + rel_y * game->player.dir_y;

	// Avoid division by zero
	if (transformed_y <= 0.01)
	{
		*screen_x = -1;
		*screen_y = -1;
		return;
	}

	depth = 1.0 / transformed_y;
	*screen_x = (int)((WIN_W / 2) * (1 + transformed_x * depth));
	*screen_y = WIN_H / 2;
}

/**
 * Draw a simple representation of a remote player (colored rectangle)
 */
static void	draw_player_sprite(t_game *game, int screen_x, int screen_y, uint32_t player_id)
{
	int	size = 10;
	int	color;
	int	x, y;

	// Different colors for different players
	switch (player_id % 4)
	{
		case 0: color = 0xFF0000; break;  // Red
		case 1: color = 0x00FF00; break;  // Green
		case 2: color = 0x0000FF; break;  // Blue
		default: color = 0xFFFF00; break; // Yellow
	}

	// Draw a simple square for the player
	y = screen_y - size;
	while (y < screen_y + size)
	{
		x = screen_x - size;
		while (x < screen_x + size)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				img_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

/**
 * Render all remote players
 */
void	render_remote_players(t_game *game)
{
	t_remote_player	*players[MAX_PLAYERS];
	int				count;
	int				i;
	int				screen_x, screen_y;

	if (!game->network.running)
		return;

	get_all_remote_players(&game->network, players, &count);

	i = 0;
	while (i < count)
	{
		if (players[i] && players[i]->active && players[i]->id != game->network.my_player_id)
		{
			world_to_screen(game, players[i]->pos_x, players[i]->pos_y, &screen_x, &screen_y);
			if (screen_x >= 0 && screen_x < WIN_W && screen_y >= 0 && screen_y < WIN_H)
			{
				draw_player_sprite(game, screen_x, screen_y, players[i]->id);
			}
		}
		i++;
	}
}

/**
 * Draw player status on screen (show connected players)
 */
void	draw_network_status(t_game *game)
{
	t_remote_player	*players[MAX_PLAYERS];
	int				count;
	int				i;

	if (!game->network.running)
		return;

	get_all_remote_players(&game->network, players, &count);

	// Draw own player ID in top-left corner
	char id_buffer[20];
	snprintf(id_buffer, sizeof(id_buffer), "Player ID: %u", game->network.my_player_id);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 20, 0xFFFFFF, id_buffer);

	// Draw connected players count
	char count_buffer[20];
	snprintf(count_buffer, sizeof(count_buffer), "Connected: %d", count + 1);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 40, 0xFFFFFF, count_buffer);

	// Draw each connected player ID
	i = 0;
	while (i < count)
	{
		if (players[i] && players[i]->active)
		{
			char player_buffer[20];
			snprintf(player_buffer, sizeof(player_buffer), "Player %u", players[i]->id);
			mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 60 + (i * 20), 0x00FF00, player_buffer);
		}
		i++;
	}
}
