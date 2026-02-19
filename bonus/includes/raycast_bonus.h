/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_BONUS_H
# define RAYCAST_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== RAYCASTING FUNCTIONS ========== */
void	raycast(t_game *game);
void	init_ray(t_game *game, int x);
void	dda(t_game *game);
void	init_step_and_side_dist(t_game *game);
void	perpendicular_wall_distance(t_raycast *ray, t_game *game);
void	draw_column(t_game *game, int x);

#endif /* RAYCAST_BONUS_H */
