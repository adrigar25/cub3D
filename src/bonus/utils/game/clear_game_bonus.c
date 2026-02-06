#include "../../cub3d_bonus.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	destroy_texture_images(t_game *game)
{
	t_texture	*cur;

	if (!game || !game->mlx_ptr)
		return ;
	if (game->txt_no && game->txt_no->img.img)
		mlx_destroy_image(game->mlx_ptr, game->txt_no->img.img);
	if (game->txt_so && game->txt_so->img.img)
		mlx_destroy_image(game->mlx_ptr, game->txt_so->img.img);
	if (game->txt_we && game->txt_we->img.img)
		mlx_destroy_image(game->mlx_ptr, game->txt_we->img.img);
	if (game->txt_ea && game->txt_ea->img.img)
		mlx_destroy_image(game->mlx_ptr, game->txt_ea->img.img);
	if (game->txt_door && game->txt_door->img.img)
		mlx_destroy_image(game->mlx_ptr, game->txt_door->img.img);
	cur = game->sprites;
	while (cur)
	{
		if (cur->img.img)
			mlx_destroy_image(game->mlx_ptr, cur->img.img);
		cur = cur->next;
	}
}

static int	ptr_in_list(t_texture *head, t_texture *ptr)
{
	while (head)
	{
		if (head == ptr)
			return (1);
		head = head->next;
	}
	return (0);
}

static void	free_texture_paths(t_game *game)
{
	t_texture	*cur;

	if (game->txt_no && game->txt_no->path)
		free(game->txt_no->path);
	if (game->txt_so && game->txt_so->path)
		free(game->txt_so->path);
	if (game->txt_we && game->txt_we->path)
		free(game->txt_we->path);
	if (game->txt_ea && game->txt_ea->path)
		free(game->txt_ea->path);
	if (game->txt_door && game->txt_door->path)
		free(game->txt_door->path);
	cur = game->sprites;
	while (cur)
	{
		if (cur->path)
			free(cur->path);
		if (cur->name)
			free(cur->name);
		cur = cur->next;
	}
}

static void	free_textures_list(t_game *game)
{
	t_texture	*cur;
	t_texture	*next;

	cur = game->sprites;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	game->sprites = NULL;
}

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx_ptr && game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	destroy_texture_images(game);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_texture_paths(game);
	// Libera los nodos de la lista de sprites
	free_textures_list(game);
	// Si las texturas core no pertenecen a la lista, libéralas también
	if (game->txt_no && !ptr_in_list(game->sprites, game->txt_no))
		free(game->txt_no);
	if (game->txt_so && !ptr_in_list(game->sprites, game->txt_so))
		free(game->txt_so);
	if (game->txt_we && !ptr_in_list(game->sprites, game->txt_we))
		free(game->txt_we);
	if (game->txt_ea && !ptr_in_list(game->sprites, game->txt_ea))
		free(game->txt_ea);
	if (game->txt_door && !ptr_in_list(game->sprites, game->txt_door))
		free(game->txt_door);
	free_map(game->map);
	free(game);
}
