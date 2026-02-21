/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_score.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:59 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 16:47:25 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "game_bonus.h"
#include "render_bonus.h"
#include"mlx.h"

void	draw_score(t_game *game)
{
	char	*score_str;
	int		x;
	int		y;

	if (!game || !game->win_ptr)
		return ;
	score_str = ft_itoa(game->score);
	if (!score_str)
		return ;
	x = 10;
	y = 10;
	mlx_string_put(game->mlx_ptr, game->win_ptr, x, y, 0xFFFFFF, "Score:");
	mlx_string_put(game->mlx_ptr, game->win_ptr, x + 60, y, 0xFFFFFF,
		score_str);
	free(score_str);
}
