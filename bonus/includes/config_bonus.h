/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 22:20:45 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_BONUS_H
# define CONFIG_BONUS_H

/* ========== MOVEMENT CONSTANTS ========== */
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.008
# define MOUSE_SENSITIVITY 0.003
/* Sprint multiplier applied when holding Shift */
# ifndef SPRINT_MULTIPLIER
#  define SPRINT_MULTIPLIER 1.8
# endif

/* ========== PLAYER CONSTANTS ========== */
# define PLAYER_HITBOX 0.25

/* ========== MINIMAP CONFIGURATION ========== */

# ifndef MINIMAP_H
#  define MINIMAP_H 200
# endif

# ifndef MINIMAP_W
#  define MINIMAP_W 200
# endif

# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE 30
# endif

# ifndef MINIMAP_BORDER
#  define MINIMAP_BORDER 2
# endif

# ifndef MINIMAP_PLAYER_SIZE
#  define MINIMAP_PLAYER_SIZE 5
# endif

# ifndef MINIMAP_PLAYER_COLOR
#  define MINIMAP_PLAYER_COLOR 0x0000FF
# endif

# ifndef MINIMAP_WALL_COLOR
#  define MINIMAP_WALL_COLOR 0x666666
# endif

# ifndef MINIMAP_FLOOR_COLOR
#  define MINIMAP_FLOOR_COLOR 0x9c9c9c
# endif

# ifndef MINIMAP_DOOR_COLOR
#  define MINIMAP_DOOR_COLOR 0x8B4513
# endif

# ifndef MINIMAP_EXIT_COLOR
#  define MINIMAP_EXIT_COLOR 0x00CC44
# endif

/* ========== PERFORMANCE ========== */
# ifndef SPRITE_SCAN_RADIUS_TILES
#  define SPRITE_SCAN_RADIUS_TILES 8
# endif

/* ========== ENEMY CONFIGURATION ========== */
# ifndef ENEMY_AGGRO_RANGE_TILES
#  define ENEMY_AGGRO_RANGE_TILES 8
# endif
# ifndef ENEMY_SPEED
#  define ENEMY_SPEED 0.008
# endif
# ifndef ENEMY_FOV_DEG
#  define ENEMY_FOV_DEG 90
# endif

// Greater values = slower animation.
# ifndef ENEMY_ANIM_SPEED_FRAMES
#  define ENEMY_ANIM_SPEED_FRAMES 30
# endif

/* ========== CROSSHAIR CONFIGURATION ========== */

# ifndef CROSSHAIR_SIZE
#  define CROSSHAIR_SIZE 10
# endif

# ifndef CROSSHAIR_COLOR
#  define CROSSHAIR_COLOR 0x00FF00
# endif

# ifndef CROSSHAIR_THICKNESS
#  define CROSSHAIR_THICKNESS 2.5
# endif

#endif /* CONFIG_BONUS_H */
