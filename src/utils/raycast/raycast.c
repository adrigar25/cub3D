/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:05:09 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 16:28:41 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, x);
		dda(game);
		draw_column(game, x);
		x++;
	}
}
