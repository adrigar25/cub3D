/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== DATA INITIALIZATION & LOADING ========== */
t_game		*init_data(void);
int			read_data(t_game **game_data, char *file);
int			check_data(t_game *game_data);

/* ========== TEXTURE MANAGEMENT ========== */
int			push_texture(t_game *game, t_texture *new_texture);
int			assign_wall_texture(t_game *game, char *key, t_texture *texture);
t_texture	*create_texture(char *key, char *value);
int			process_texture(t_game *game, char *key, char *value);

/* ========== LINE PARSER ========== */
void		update_allowed_chars(t_game *game, char c);
int			process_config_line(t_game *game, char *line);

/* ========== COLOR / RGB UTILITIES ========== */
int			rgb_to_hex(int r, int g, int b);
int			check_rgb_format(char *values);
int			parse_rgb(char *line);

#endif /* PARSE_BONUS_H */
