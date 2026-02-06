/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:03:21 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/05 22:36:01 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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

int	load_sprites_images(t_game *game)
{
	t_texture	*current;

	if (load_texture(game, &game->txt_door->img, game->txt_door->path) == -1)
		return (-1);
	if (load_texture(game, &game->txt_no->img, game->txt_no->path) == -1)
		return (-1);
	if (load_texture(game, &game->txt_so->img, game->txt_so->path) == -1)
		return (-1);
	if (load_texture(game, &game->txt_ea->img, game->txt_ea->path) == -1)
		return (-1);
	if (load_texture(game, &game->txt_we->img, game->txt_we->path) == -1)
		return (-1);
	/* Enemy textures (optional) */
	if (game->e_txt_s && game->e_txt_s->path)
		if (load_texture(game, &game->e_txt_s->img, game->e_txt_s->path) == -1)
			return (-1);
	if (game->e_txt_w1 && game->e_txt_w1->path)
		if (load_texture(game, &game->e_txt_w1->img, game->e_txt_w1->path) ==
			-1)
			return (-1);
	if (game->e_txt_w2 && game->e_txt_w2->path)
		if (load_texture(game, &game->e_txt_w2->img, game->e_txt_w2->path) ==
			-1)
			return (-1);
	current = game->sprites;
	while (current)
	{
		if (load_texture(game, &current->img, current->path) == -1)
			return (-1);
		current = current->next;
	}
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
