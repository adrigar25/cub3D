/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:10:35 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

/* ========== MAP DATA STRUCTURE ========== */
# include "types.h"

/* ========== MAP VALIDATION ========== */
int		read_map(char ***map, int fd);
int		check_map(char **map);
int		check_walls(char **map);
int		check_empty_rows(char **map);
int		check_empty_columns(char **map);
int		check_valid_characters(char **map);
int		check_player(char **map);
void	free_map(char **map);

#endif /* MAP_H */
