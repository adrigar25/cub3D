/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 17:10:05 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

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

/* ========== IMAGE STRUCTURE ========== */
typedef struct s_img {
  void *img;
  char *addr;
  int bpp;
  int line_len;
  int endian;
  int width;
  int height;
}						t_img;

/* ========== TEXTURES STRUCTURE ========== */
typedef struct s_textures {
  t_img no;
  char *path_no;
  t_img so;
  char *path_so;
  t_img ea;
  char *path_ea;
  t_img we;
  char *path_we;
  int color_c;
  int color_f;
}						t_textures;

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
