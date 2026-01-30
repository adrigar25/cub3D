/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:52 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/29 23:54:26 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                               LIBRARIES                                    */
/* ************************************************************************** */

# include "../../libs/libft/libft.h"
# include "../../libs/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
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

/* ************************************************************************** */
/*                               WINDOW DIMENSIONS                            */
/* ************************************************************************** */
# ifndef WIN_W
#  define WIN_W 1280
# endif

# ifndef WIN_H
#  define WIN_H 720
# endif

/* ************************************************************************** */
/*                               KEY MAPPING                                  */
/* ************************************************************************** */

// MACOS Keycodes
# define KEY_W_M 13
# define KEY_A_M 2
# define KEY_S_M 1
# define KEY_D_M 0
# define KEY_LEFT_M 124
# define KEY_RIGHT_M 123
# define KEY_UP_M 126
# define KEY_DOWN_M 125
# define KEY_ESC_M 53

// LINUX Keycodes
# define KEY_W_L 119
# define KEY_A_L 97
# define KEY_S_L 115
# define KEY_D_L 100
# define KEY_LEFT_L 65361
# define KEY_RIGHT_L 65363
# define KEY_UP_L 65362
# define KEY_DOWN_L 65364
# define KEY_ESC_L 65307

/* ************************************************************************** */
/*                               CONSTANTS                                    */
/* ************************************************************************** */

# define SHADOW_MASK 0x7F7F7F

// Movement constants
# define MOVE_SPEED 0.07
# define ROT_SPEED 0.03

// Texture constants
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

/**
 * ENGLISH: Key states structure for continuous movement.
 *
 * SPANISH: Estructura de estados de teclas para movimiento continuo.
 */
typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			up;
	int			down;
}				t_keys;

/**
 * ENGLISH: Image structure for pixel manipulation.
 *
 * This structure is used to store information about the image
 * being processed, including its memory address and other
 * necessary parameters for pixel manipulation.
 *
 * SPANISH: Estructura de imagen para manipulación de píxeles.
 *
 * Esta estructura se utiliza para almacenar información sobre la imagen
 * que se está procesando, incluyendo su dirección de memoria y otros
 * parámetros necesarios para la manipulación de píxeles.
 *
 * @param img Pointer to the image created by MLX
 * @param addr Memory address of the image data
 * @param bpp Bits per pixel
 * @param line_len Length of a line in bytes
 * @param endian Endianness of the image data
 */
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;
typedef struct s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	int			color_f;
	int			color_c;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
}				t_texture;

typedef struct s_raycast
{
	// Posición de la camara
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	// Posición del mapa
	int			map_x;
	int			map_y;
	// Paso del DDA
	int			step_x;
	int			step_y;
	// Distancias del DDA
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	// Distancia perpendicular a la pared (Sin ojo de pez)
	double		perp_wall_dist;
	// Colision
	int			side;
	int			hit;
	// Altura de la línea a dibujar
	int			line_height;
	// Límites de dibujo
	int			draw_start;
	int			draw_end;
	// Texture calculations
	// Exact position where wall was hit
	double		wall_x;
	// X coordinate on texture
	int			tex_x;
	// How much to increase texture coordinate per screen pixel
	double		step;
	// Current texture position
	double		tex_pos;
}				t_raycast;
typedef struct s_game
{
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_texture	textures;
	t_player	player;
	t_raycast	raycast;
	t_keys		keys;
}				t_game;

/* ************************************************************************** */
/*                               FUNCTION PROTOTYPES                          */
/* ************************************************************************** */

// Map utilities
int				read_map(char ***map, int fd);
int				check_map(char **map);
int				check_walls(char **map);
int				check_empty_rows(char **map);
int				check_empty_columns(char **map);
int				check_valid_characters(char **map);
int				check_player(char **map);

// Data utilities
int				check_data(t_game *game_data);

// Player utilities
int				is_player_char(char c);
int				get_player_position(t_game *game);

// Initialization
int				read_data(t_game **game_data, char *file);
t_game			*init_data(void);

// MLX Initialization
int				init_mlx(t_game *game);
int				init_textures(t_game *game);
int				load_textures_images(t_game *game);

// Raycasting
void			raycast(t_game *game);
void			init_ray(t_game *game, int x);
void			dda(t_game *game);
void			init_step_and_side_dist(t_game *game);
void			perpendicular_wall_distance(t_raycast *ray, t_game *game);
void			draw_column(t_game *game, int x);

// Utils
int				rgb_to_hex(int r, int g, int b);
int				check_rgb_format(char *values);
int				parse_rgb(char *line);
void			clear_game(t_game *game);
void			free_map(char **map);

// Player movement functions
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
int				is_valid_position(t_game *game, double x, double y);

// Image buffer functions
int				init_image_buffer(t_game *game);
void			img_pixel_put(t_img *img, int x, int y, int color);
void			render_frame(t_game *game);
int				get_texture_color(t_img *texture, int x, int y);

// Game loop functions
void			start_game_loop(t_game *game);

// Key handling functions
void			init_keys(t_game *game);
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);
void			update_movement(t_game *game);

// Print
long			ft_error(const char *function, char **str);
long			ft_putcolor(int fd, int color);
long			ft_putstr_fd_color(const char *str, int fd, int color);

#endif // CUB3D_H
