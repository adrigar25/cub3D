/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:52 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 18:44:36 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	int		*color_floor;
	int		*color_ceiling;
	char	**map;
}			t_game;

int			handle_error(const char *message);

// Map utilities
int			read_map(char ***map, int fd);
void		free_map(char **map);
int			check_map(char **map);

// Initialization
t_game		*init_game(char *file);
int			init_data_structs(t_game *game);

#endif // CUB3D_H