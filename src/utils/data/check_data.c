/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:50:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/07 15:43:47 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_data(t_game *game_data)
{
	if (!game_data->textures.no.img || !game_data->textures.so.img
		|| !game_data->textures.we.img || !game_data->textures.ea.img)
		return (ft_error("check_data", (char *[]){"Missing texture images",
				NULL}), -1);
	if (game_data->textures.color_floor == -1
		|| game_data->textures.color_ceiling == -1)
		return (ft_error("check_data",
				(char *[]){"Missing floor or ceiling color", NULL}), -1);
	if (game_data->textures.color_ceiling == -2
		|| game_data->textures.color_floor == -2)
		return (ft_error("check_data",
				(char *[]){"Invalid RGB values for floor or ceiling", NULL}),
			-1);
	return (0);
}
