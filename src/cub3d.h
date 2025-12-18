/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:52 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 01:08:59 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 800
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 600
# endif

typedef struct s_game
{
	void	*no_ptr;
	void	*so_ptr;
	void	*we_ptr;
	void	*ea_ptr;
	void	*mlx_ptr;
	void	*win_ptr;
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

// MLX Initialization
int			init_mlx(t_game *game);
int			init_textures(t_game *game);

#endif // CUB3D_H
