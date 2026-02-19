/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

# include "types_bonus.h"

typedef struct s_game	t_game;

/* ========== WINDOW DIMENSIONS ========== */
# ifndef WIN_W
#  define WIN_W 1280
# endif

# ifndef WIN_H
#  define WIN_H 720
# endif

/* ========== TEXTURE CONSTANTS ========== */
# define TEX_WIDTH		64
# define TEX_HEIGHT		64

/* ========== SHADOW & EFFECTS ========== */
# define SHADOW_MASK	0x7F7F7F

/* ========== CROSSHAIR ========== */
# ifndef CROSSHAIR_SIZE
#  define CROSSHAIR_SIZE		10
# endif
# ifndef CROSSHAIR_COLOR
#  define CROSSHAIR_COLOR	0x00FF00
# endif
# ifndef CROSSHAIR_THICKNESS
#  define CROSSHAIR_THICKNESS	2
# endif

/* ========== MLX INITIALIZATION ========== */
int		init_mlx(t_game *game);
int		load_images(t_game *game);

/* ========== IMAGE BUFFER ========== */
int		init_image_buffer(void *mlx_ptr, t_img *img, int width, int height);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	render_frame(t_game *game);
int		get_texture_color(t_img *texture, int x, int y);

/* ========== HUD ========== */
void	draw_hud_message(t_game *game, t_hud msg);

#endif /* RENDER_BONUS_H */
