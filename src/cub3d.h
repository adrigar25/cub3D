/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:52 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/18 15:18:34 by adriescr         ###   ########.fr       */
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

/* ************************************************************************** */
/*                               COLOR CONSOLE                                */
/* ************************************************************************** */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define ORANGE "\033[38;5;208m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

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

// Map utilities
int			read_map(char ***map, int fd);
void		free_map(char **map);
int			check_map(char **map);

// Initialization
t_game		*read_data(char *file);
int			init_data_structs(t_game *game);

// MLX Initialization
int			init_mlx(t_game *game);
int			init_textures(t_game *game);

// Utils
void		parse_rgb(char *line, int *color);
void		clear_game(t_game *game);
// Print
long		ft_error(const char *function, char **str);
long		ft_putcolor(int fd, int color);
long		ft_putstr_fd_color(const char *str, int fd, int color);

#endif // CUB3D_H
