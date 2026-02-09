/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/06 16:34:12 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* ========== MAP UTILITIES ========== */
int		read_map(char ***map, int fd);
int		check_map(char **map);
int		check_walls(char **map);
int		check_empty_rows(char **map);
int		check_empty_columns(char **map);
int		check_valid_characters(char **map);
int		check_player(char **map);

/* ========== DATA UTILITIES ========== */
int		check_data(t_game *game_data);

/* ========== PLAYER UTILITIES ========== */
int		is_player_char(char c);
int		get_player_position(t_game *game);

/* ========== INITIALIZATION ========== */
int		read_data(t_game **game_data, char *file);
t_game	*init_data(void);

/* ========== MLX INITIALIZATION ========== */
int		init_mlx(t_game *game);
int		init_textures(t_game *game);
int		load_textures_images(t_game *game);

/* ========== RAYCASTING ========== */
void	raycast(t_game *game);
void	init_ray(t_game *game, int x);
void	dda(t_game *game);
void	init_step_and_side_dist(t_game *game);
void	perpendicular_wall_distance(t_raycast *ray, t_game *game);
void	draw_column(t_game *game, int x);

/* ========== UTILS ========== */
int		rgb_to_hex(int r, int g, int b);
int		check_rgb_format(char *values);
int		parse_rgb(char *line);
void	clear_game(t_game *game);
void	free_map(char **map);

/* ========== PLAYER MOVEMENT ========== */
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	rotate_player(t_game *game, double angle);
int		is_valid_position(t_game *game, double x, double y);

/* ========== IMAGE BUFFER ========== */
int		init_image_buffer(t_game *game);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	render_frame(t_game *game);
int		get_texture_color(t_img *texture, int x, int y);

/* ========== GAME LOOP ========== */
void	start_game_loop(t_game *game);

/* ========== KEY HANDLING ========== */
void	init_keys(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
void	update_movement(t_game *game);

/* ========== PRINT UTILITIES ========== */
long	ft_error(const char *function, char **str);
long	ft_putcolor(int fd, int color);
long	ft_putstr_fd_color(const char *str, int fd, int color);

#endif /* FUNCTIONS_H */
