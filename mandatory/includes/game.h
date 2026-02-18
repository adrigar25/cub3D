/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:10:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "render.h"
# include "player.h"
# include "raycast.h"

/* ========== GAME STRUCTURE ========== */
/**
 * Main game container. Includes all subsystems:
 * map, textures, player, raycast state and key states.
 */
typedef struct s_game
{
	char				**map;
	int					map_w;
	int					map_h;
	double				zbuffer[1280];
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_textures			textures;
	t_player			player;
	t_raycast			raycast;
	t_keys				keys;
}						t_game;

/* ========== GAME LOOP ========== */
void	start_game_loop(t_game *game);

/* ========== CLEANUP ========== */
void	clear_game(t_game *game);

/* ========== PRINT UTILITIES ========== */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define ORANGE "\033[38;5;208m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

long	ft_error(const char *function, char **str);
long	ft_putcolor(int fd, int color);
long	ft_putstr_fd_color(const char *str, int fd, int color);

#endif /* GAME_H */
