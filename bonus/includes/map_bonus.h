/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/21 20:20:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BONUS_H
# define MAP_BONUS_H

typedef struct s_game	t_game;

/* ========== MAP DATA STRUCTURE ========== */
typedef struct s_map_data
{
	char				**grid;
	int					width;
	int					height;
}						t_map_data;

/* ========== MAP VALIDATION ========== */
int						read_map(t_game *game, int fd, char *first_line);
int						check_map(t_game *game);
int						check_walls(char **map);
int						check_empty_rows(char **map);
int						check_empty_columns(char **map);
int						check_valid_characters(t_game *game);
int						check_player(char **map);
int						is_map_line(t_game *game, char *line);
void					free_map(char **map);

#endif /* MAP_BONUS_H */
