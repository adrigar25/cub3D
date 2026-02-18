/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 01:19:27 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_BONUS_H
# define FUNCTIONS_BONUS_H

# include "structs_bonus.h"

/* ========== MAP UTILITIES ========== */
int			read_map(t_game *game, int fd, char *first_line);
int			check_map(t_game *game);
int			check_walls(char **map);
int			check_empty_rows(char **map);
int			check_empty_columns(char **map);
int			check_valid_characters(t_game *game);
int			check_player(char **map);
int			is_map_line(t_game *game, char *line);

/* ========== MINIMAP UTILITIES ========== */
void		draw_player(t_game *game, double center_x, double center_y);
int			render_minimap(t_game *game);

/* ========== DATA UTILITIES ========== */
int			check_data(t_game *game_data);
/* ========== TEXTURE MANAGEMENT ========== */
int			push_texture(t_game *game, t_texture *new_texture);
int			assign_wall_texture(t_game *game, char *key, t_texture *texture);
t_texture	*create_texture(char *key, char *value);
int			process_texture(t_game *game, char *key, char *value);

/* ========== LINE PARSER ========== */
void		update_allowed_chars(t_game *game, char c);
int			process_config_line(t_game *game, char *line);

/* ========== PLAYER UTILITIES ========== */
int			is_player_char(char c);
int			get_player_position(t_game *game);

/* ========== INITIALIZATION ========== */
int			read_data(t_game **game_data, char *file);
t_game		*init_data(void);

/* ========== MLX INITIALIZATION ========== */
int			init_mlx(t_game *game);
int			load_images(t_game *game);

/* ========== RAYCASTING ========== */
void		raycast(t_game *game);
void		init_ray(t_game *game, int x);
void		dda(t_game *game);
void		init_step_and_side_dist(t_game *game);
void		perpendicular_wall_distance(t_raycast *ray, t_game *game);
void		draw_column(t_game *game, int x);

/* ========== SPRITES ========== */
void		sprite_render(t_game *game);
void		sprite_draw_at(t_game *game, t_img *texture, double world_x,
				double world_y);

/* ========== UTILS ========== */
int			rgb_to_hex(int r, int g, int b);
int			check_rgb_format(char *values);
int			parse_rgb(char *line);
void		clear_game(t_game *game, int exit_code);
void		free_map(char **map);

/* ========== PLAYER MOVEMENT ========== */
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
void		rotate_player(t_game *game, double angle);
int			handle_mouse_press(int button, int x, int y, t_game *game);
int			handle_mouse_move(int x, int y, t_game *game);
int			is_valid_position(t_game *game, double x, double y);

/* ========== IMAGE BUFFER ========== */
int			init_image_buffer(void *mlx_ptr, t_img *img, int width, int height);
void		img_pixel_put(t_img *img, int x, int y, int color);
void		render_frame(t_game *game);
int			get_texture_color(t_img *texture, int x, int y);

/* ========== HUD MESSAGE ========== */
void		draw_hud_message(t_game *game, t_hud msg);

/* ========== GAME LOOP ========== */
void		start_game_loop(t_game *game);
void		check_exit_collision(t_game *game);
void		check_collectibles(t_game *game);
void		draw_score(t_game *game);

/* ========== KEY HANDLING ========== */
void		init_keys(t_game *game);
int			handle_keypress(int keycode, t_game *game);
int			handle_keyrelease(int keycode, t_game *game);
void		update_movement(t_game *game);

/* ========== DOOR UTILITIES ========== */
void		open_door(t_game *game);

/* ========== MINIMAP UTILITIES ========== */
int			has_floor_nearby(t_game *game, int x, int y);
void		put_minimap_tile(t_game *game, int px, int py, double world_x);
void		clear_map(t_game *game);

/* ========== PRINT UTILITIES ========== */
long		ft_error(const char *function, char **str);
long		ft_putcolor(int fd, int color);
long		ft_putstr_fd_color(const char *str, int fd, int color);

/* ========== ENEMY ========== */
t_enemy		*create_enemy(int tile_x, int tile_y);
void		enemy_add(t_game *game, t_enemy *node);
void		enemy_clear(t_enemy **list);
void		enemy_collect_from_map(t_game *game);
void		enemy_update_ai(t_game *game);
int			enemy_can_see_player(t_game *game, t_enemy *e);

#endif /* FUNCTIONS_BONUS_H */
