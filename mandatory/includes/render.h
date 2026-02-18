/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:44:15 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"

typedef struct s_game	t_game;

/* ========== WINDOW DIMENSIONS ========== */
# ifndef WIN_W
#  define WIN_W 1280
# endif

# ifndef WIN_H
#  define WIN_H 720
# endif

/* ========== TEXTURE CONSTANTS ========== */
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/* ========== SHADOW & EFFECTS ========== */
# define SHADOW_MASK 0x7F7F7F

/* ========== MLX INIT ========== */
int						init_mlx(t_game *game);
int						init_textures(t_game *game);
int						load_textures_images(t_game *game);

/* ========== IMAGE BUFFER ========== */
int						init_image_buffer(t_game *game);
void					img_pixel_put(t_img *img, int x, int y, int color);
void					render_frame(t_game *game);
int						get_texture_color(t_img *texture, int x, int y);

#endif /* RENDER_H */
