/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:11:02 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "game.h"

/* ========== DATA INITIALIZATION & LOADING ========== */
t_game	*init_data(void);
int		read_data(t_game **game_data, char *file);
int		check_data(t_game *game_data);

/* ========== COLOR / RGB UTILITIES ========== */
int		rgb_to_hex(int r, int g, int b);
int		check_rgb_format(char *values);
int		parse_rgb(char *line);

#endif /* PARSE_H */
