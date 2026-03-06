/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_BONUS_H
# define ENEMY_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== ENEMY CONFIGURATION ========== */
# ifndef ENEMY_AGGRO_RANGE_TILES
#  define ENEMY_AGGRO_RANGE_TILES	8
# endif
# ifndef ENEMY_SPEED
#  define ENEMY_SPEED				0.008
# endif
# ifndef ENEMY_FOV_DEG
#  define ENEMY_FOV_DEG				90
# endif
# ifndef ENEMY_ANIM_SPEED_FRAMES
#  define ENEMY_ANIM_SPEED_FRAMES	30
# endif

/* ========== ENEMY FUNCTIONS ========== */
t_enemy	*create_enemy(int tile_x, int tile_y);
void	enemy_add(t_game *game, t_enemy *node);
void	enemy_clear(t_enemy **list);
void	enemy_collect_from_map(t_game *game);
void	enemy_update_ai(t_game *game);
int		enemy_can_see_player(t_game *game, t_enemy *e);

#endif /* ENEMY_BONUS_H */
