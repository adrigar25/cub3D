/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/09 16:23:37 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

/* ========== KEY STATES ========== */
/**
 * ENGLISH: Key states structure for continuous movement.
 *
 * SPANISH: Estructura de estados de teclas para movimiento continuo.
 */
typedef struct s_keys
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
	int					up;
	int					down;
	int					shift;
}						t_keys;

/* ========== ENEMY STRUCTURE ========== */
typedef struct s_enemy
{
	float				x;
	float				y;
	int					tile_x;
	int					tile_y;
	float				last_x;
	float				last_y;
	int					moving;
	int					anim_frame;
	int					anim_timer;
	struct s_enemy		*next;
}						t_enemy;
/* ========== IMAGE STRUCTURE ========== */
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
		t_enemy             *enemies;
 */
typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_img;

/* ========== PLAYER STRUCTURE ========== */
typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				vertical_dir_x;
	double				vertical_dir_y;
	double				plane_x;
	double				plane_y;
	int					pitch;
}						t_player;

/* ========== TEXTURE STRUCTURE ========== */
typedef struct s_texture
{
	char				*name;
	char				*path;
	t_img				img;
	struct s_texture	*next;
}						t_texture;

/* ========== SPRITE INFO STRUCTURE ========== */
typedef struct s_sprite_info
{
	double				x;
	double				y;
	double				depth;
	t_img				*tex;
}						t_sprite_info;

/* ========== RAYCAST STRUCTURE ========== */
typedef struct s_raycast
{
	// Posición de la camara
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	// Posición del mapa
	int					map_x;
	int					map_y;
	// Paso del DDA
	int					step_x;
	int					step_y;
	// Distancias del DDA
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	// Distancia perpendicular a la pared (Sin ojo de pez)
	double				perp_wall_dist;
	// Colision
	int					side;
	int					hit;
	// Altura de la línea a dibujar
	int					line_height;
	// Límites de dibujo
	int					draw_start;
	int					draw_end;
	// Texture calculations
	// Exact position where wall was hit
	double				wall_x;
	// X coordinate on texture
	int					tex_x;
	// How much to increase texture coordinate per screen pixel
	double				step;
	// Current texture position
	double				tex_pos;
}						t_raycast;

/* ========== GAME STRUCTURE ========== */
typedef struct s_game
{
	char				**map;
	int					map_w;
	int					map_h;
	int					mouse_captured;
	double				zbuffer[WIN_W];
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				minimap;
	t_img				img;
	t_texture			*txt_no;
	t_texture			*txt_so;
	t_texture			*txt_ea;
	t_texture			*txt_we;
	t_texture			*txt_door;
	t_texture			*e_txt_s;
	t_texture			*e_txt_w1;
	t_texture			*e_txt_w2;
	t_texture			*sprites;
	int					floor_color;
	int					ceiling_color;
	t_enemy				*enemies;
	t_player			player;
	t_raycast			raycast;
	t_keys				keys;
	char				allowed_chars[128];
	int					allowed_count;
}						t_game;

#endif /* STRUCTS_BONUS_H */
