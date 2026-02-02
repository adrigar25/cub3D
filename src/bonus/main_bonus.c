/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:52 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 18:44:40 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * ENGLISH: Main entry point for the game
 *
 * SPANISH: Punto de entrada principal del juego
 */
int	main(void)
{
	t_game	*game_data;

	game_data = init_data();
	if (!game_data)
		return (1);

	if (init_mlx(game_data))
		return (clear_game(game_data), 1);

	init_menu(game_data);
	start_game_loop(game_data);

	clear_game(game_data);
	return (0);
}
