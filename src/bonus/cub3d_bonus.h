/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:52 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 19:03:07 by adriescr         ###   ########.fr       */
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
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <dirent.h>

/* ************************************************************************** */
/*                               NETWORKING CONSTANTS                         */
/* ************************************************************************** */

# define MAX_CLIENTS 10
# define PACKET_SIZE 64
# define DEFAULT_PORT 8080

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
# define KEY_E_M 14
# define KEY_C_M 8
# define KEY_SPACE_M 49
# define KEY_CTRL_M 256
# define KEY_SHIFT_M 257
# define KEY_S_M 1

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
# define KEY_E_L 101
# define KEY_C_L 99
# define KEY_SPACE_L 32
# define KEY_CTRL_L 65507
# define KEY_SHIFT_L 65505
# define KEY_S_L 115

/* ************************************************************************** */
/*                               CONSTANTS                                    */
/* ************************************************************************** */

# define SHADOW_MASK 0x7F7F7F

// Movement constants
# define MOVE_SPEED 0.03
# define SPRINT_SPEED 0.06
# define CROUCH_SPEED 0.015
# define ROT_SPEED 0.008
# define MOUSE_SENSITIVITY 0.003

// Height constants
# define NORMAL_HEIGHT 0.0
# define CROUCH_HEIGHT -0.3
# define JUMP_FORCE 0.15
# define GRAVITY 0.01

// Texture constants
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

// WINDOW DIMENSIONS
# ifndef WIN_W
#  define WIN_W 1280
# endif

# ifndef WIN_H
#  define WIN_H 720
# endif

# define WIN_WIDTH WIN_W
# define WIN_HEIGHT WIN_H

// MINIMAP CONSTANTS

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

# ifndef MINIMAP_FLOOR_COLOR
#  define MINIMAP_WALL_COLOR 0x666666
# endif

# ifndef MINIMAP_FLOOR_COLOR
#  define MINIMAP_FLOOR_COLOR 0x9c9c9c
# endif

# ifndef MINIMAP_DOOR_COLOR
#  define MINIMAP_DOOR_COLOR 0x8B4513
# endif

# ifndef MINIMAP_X
#  define MINIMAP_X 1070
# endif

# ifndef MINIMAP_Y
#  define MINIMAP_Y 510
# endif

// Crosshair constants
# ifndef CROSSHAIR_SIZE
#  define CROSSHAIR_SIZE 10
# endif

# ifndef CROSSHAIR_COLOR
#  define CROSSHAIR_COLOR 0x00FF00
# endif

# ifndef CROSSHAIR_THICKNESS
#  define CROSSHAIR_THICKNESS 2.5
# endif

// Player constants
# ifndef PLAYER_HITBOX
#  define PLAYER_HITBOX 0.25
# endif

// Menu constants
# define MENU_WIDTH 400
# define MENU_HEIGHT 300
# define MENU_OPTION_HEIGHT 50
# define MENU_FONT_SIZE 20

// Menu states
# define MENU_MAIN 0
# define MENU_MULTIPLAYER 1
# define MENU_MAP_SELECTION 2
# define MENU_ENTER_IP 3
# define GAME_RUNNING 4

// Network settings
# define DEFAULT_PORT 8080

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
	int			space;
	int			ctrl;
	int			shift;
}				t_keys;

/**
 * ENGLISH: Menu structure for game states and options.
 *
 * SPANISH: Estructura de menú para estados y opciones del juego.
 */
typedef struct s_menu
{
	int			state;
	int			selected_option;
	int			option_count;
	char		*options[10];
	char		**available_maps;
	int			map_count;
	int			selected_map;
	int			game_mode;
	int			mouse_x;
	int			mouse_y;
	char		server_ip[256];
	int			ip_cursor;
}				t_menu;

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
	double		vertical_dir_x;
	double		vertical_dir_y;
	double		plane_x;
	double		plane_y;
	int			pitch;
	double		height;
	double		z_velocity;
}				t_player;

typedef struct s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_img		door;
	int			color_f;
	int			color_c;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*path_door;
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
/* ************************************************************************** */
/*                               NETWORKING STRUCTURES                        */
/* ************************************************************************** */

// Packet types
# define PACKET_PLAYER_UPDATE 1
# define PACKET_DOOR_TOGGLE 2
# define PACKET_MAP_INFO 3

// Forward declaration
struct s_player;

typedef struct s_net_packet
{
	int			type;
	int			player_id;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		height;
	int			door_x;
	int			door_y;
	char		map_name[256];
}				t_net_packet;

typedef struct s_network
{
	int				is_server;
	int				server_socket;
	int				client_sockets[MAX_CLIENTS];
	int				client_count;
	struct sockaddr_in	server_addr;
	pthread_t		listen_thread;
	pthread_t		send_thread;
	int				running;
	int				my_player_id;
	struct s_player	*remote_players[MAX_CLIENTS];
	char			map_name[256];
}					t_network;

typedef struct s_game
{
	char		**map;
	int			map_w;
	int			map_h;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		minimap;
	t_img		img;
	t_texture	textures;
	t_player	player;
	t_raycast	raycast;
	t_keys		keys;
	t_network	*network;
	t_menu		menu;
}				t_game;

/* ************************************************************************** */
/*                               FUNCTION PROTOTYPES                          */
/* ************************************************************************** */

// Map utilities
int				read_map(t_game *game, int fd);
int				check_map(char **map);
int				check_walls(char **map);
int				check_empty_rows(char **map);
int				check_empty_columns(char **map);
int				check_valid_characters(char **map);
int				check_player(char **map);

// Minimap utilities
void			draw_player(t_game *game, double center_x, double center_y);
int				print_minimap(t_game *game);

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
void			clear_game_data(t_game *game);
void			free_map(char **map);

// Player movement functions
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			rotate_player(t_game *game, double angle);
int				handle_mouse(int x, int y, t_game *game);
int				is_valid_position(t_game *game, double x, double y);

// Image buffer functions
int				init_image_buffer(void *mlx_ptr, t_img *img, int width,
					int height);
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

// Door functions
void			open_door(t_game *game);

// Network functions
int				init_network(t_game *game, int is_server, const char *ip, int port);
void			cleanup_network(t_game *game);
void			broadcast_player_state(t_game *game);
void			handle_network_packets(t_game *game);
void			update_remote_players(t_game *game);
void			render_network_players(t_game *game);

// Menu functions
void			init_menu(t_game *game);
void			render_menu(t_game *game);
void			render_multiplayer_menu(t_game *game);
void			render_map_selection_menu(t_game *game);
void			render_enter_ip_menu(t_game *game);
void			handle_menu_key(int keycode, t_game *game);
void			handle_multiplayer_menu_key(int keycode, t_game *game);
void			handle_map_selection_key(int keycode, t_game *game);
void			handle_enter_ip_key(int keycode, t_game *game);
void			start_single_player(t_game *game);
void			start_multiplayer_menu(t_game *game);
void			start_map_selection(t_game *game, int mode);
void			load_available_maps(t_game *game);
void			free_available_maps(t_game *game);
void			start_server(t_game *game);
void			connect_to_server(t_game *game);
void			start_enter_ip_menu(t_game *game);

// Print
long			ft_error(const char *function, char **str);
long			ft_putcolor(int fd, int color);
long			ft_putstr_fd_color(const char *str, int fd, int color);

#endif // CUB3D_H
