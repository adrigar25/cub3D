/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:03:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/28 12:59:55 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	load_texture(t_game *game, t_img *img, char *path)
{
	if (!path)
		return (ft_fprintf(2, RED "Error: Texture path is NULL\n" RESET), -1);
	img->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
		return (ft_fprintf(2, RED "Error: Loading img %s\n" RESET, path), -1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

int	load_textures_images(t_game *game)
{
	if (load_texture(game, &game->textures.no, game->textures.path_no) == -1)
		return (-1);
	if (load_texture(game, &game->textures.so, game->textures.path_so) == -1)
		return (-1);
	if (load_texture(game, &game->textures.we, game->textures.path_we) == -1)
		return (-1);
	if (load_texture(game, &game->textures.ea, game->textures.path_ea) == -1)
		return (-1);
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_fprintf(2, "Error: Failed to initialize MLX\n"), -1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "Cub3D");
	if (!game->win_ptr)
		return (ft_fprintf(2, "Error: Failed to create window\n"), -1);
	if (!init_image_buffer(game->mlx_ptr, &game->img, WIN_W, WIN_H))
		return (ft_fprintf(2, "Error: Failed to create image buffer\n"), -1);
	if (!init_image_buffer(game->mlx_ptr, &game->minimap, MINIMAP_W, MINIMAP_H))
		return (ft_fprintf(2, "Error: Failed to create minimap buffer\n"), -1);
	return (0);
}
