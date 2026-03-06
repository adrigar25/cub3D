/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:06:54 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "enemy_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"
#include "mlx.h"
#include "render_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Frees a NULL-terminated array of map row strings.
 *
 * SPANISH: Libera un array de cadenas de filas de mapa terminado en NULL.
 *
 * @param map NULL-terminated array of strings. /
 *            Array de cadenas terminado en NULL.
 */
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

/**
 * ENGLISH: Frees all nodes in a texture linked list and their resources.
 *
 * SPANISH: Libera todos los nodos de una lista enlazada de texturas
 *          junto con sus recursos.
 *
 * @param mlx MLX instance pointer (may be NULL). /
 *            Puntero a la instancia MLX (puede ser NULL).
 * @param head Head of the texture linked list. /
 *             Cabeza de la lista enlazada de texturas.
 */
static void	free_texture_list(void *mlx, t_texture *head)
{
	t_texture	*cur;
	t_texture	*next;

	if (!head)
		return ;
	cur = head;
	while (cur)
	{
		next = cur->next;
		if (cur->path)
			free(cur->path);
		if (cur->name)
			free(cur->name);
		if (mlx && cur->img.img)
			mlx_destroy_image(mlx, cur->img.img);
		free(cur);
		cur = next;
	}
}

/**
 * ENGLISH: Releases all texture resources stored in the game structure.
 *
 * SPANISH: Libera todos los recursos de textura almacenados en la
 *          estructura del juego.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 */
static void	free_textures(t_game *game)
{
	if (!game)
		return ;
	free_texture_list(game->mlx_ptr, game->txt_no);
	free_texture_list(game->mlx_ptr, game->txt_so);
	free_texture_list(game->mlx_ptr, game->txt_ea);
	free_texture_list(game->mlx_ptr, game->txt_we);
	free_texture_list(game->mlx_ptr, game->txt_door);
	free_texture_list(game->mlx_ptr, game->txt_exit);
	free_texture_list(game->mlx_ptr, game->e_txt_s);
	free_texture_list(game->mlx_ptr, game->e_txt_w1);
	free_texture_list(game->mlx_ptr, game->e_txt_w2);
	free_texture_list(game->mlx_ptr, game->sprites);
	game->txt_no = NULL;
	game->txt_so = NULL;
	game->txt_ea = NULL;
	game->txt_we = NULL;
	game->txt_door = NULL;
	game->txt_exit = NULL;
	game->e_txt_s = NULL;
	game->e_txt_w1 = NULL;
	game->e_txt_w2 = NULL;
	game->sprites = NULL;
}

/**
 * ENGLISH: Renders the end-of-game HUD based on the exit code (victory
 *          or defeat).
 *
 * SPANISH: Renderiza el HUD de fin de partida según el código de salida
 *          (victoria o derrota).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param exit_code 1 for victory, 2 for defeat. /
 *                  1 para victoria, 2 para derrota.
 */
static void	draw_finish_hud(t_game *game, int exit_code)
{
	t_hud	msg;

	msg.sub2 = "Press ESC to exit";
	if (exit_code == 1)
	{
		msg.color = 0x00FF55;
		msg.title = "VICTORY!";
		msg.sub = "You reached the exit!";
	}
	else if (exit_code == 2)
	{
		msg.color = 0xFF0000;
		msg.title = "GAME OVER";
		msg.sub = "You died!";
	}
	draw_hud_message(game, msg);
}

/**
 * ENGLISH: Frees all game resources and optionally shows the end screen.
 *          exit_code -1 frees memory and exits cleanly; 1/2 shows HUD.
 *
 * SPANISH: Libera todos los recursos del juego y muestra la pantalla
 *          de fin si corresponde. exit_code -1 libera y sale; 1/2 HUD.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param exit_code -1 to free resources, 1/2 to show end HUD. /
 *                  -1 para liberar, 1/2 para mostrar HUD final.
 */
void	clear_game(t_game *game, int exit_code)
{
	if (exit_code == -1)
	{
		ft_fprintf(1, GREEN "Exiting game. Goodbye!\n" RESET);
		if (!game)
			return ;
		if (game->mlx_ptr && game->img.img)
			mlx_destroy_image(game->mlx_ptr, game->img.img);
		if (game->mlx_ptr && game->minimap.img)
			mlx_destroy_image(game->mlx_ptr, game->minimap.img);
		free_textures(game);
		if (game->mlx_ptr && game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		enemy_clear(&game->enemies);
		free_map(game->map.grid);
		if (game->zbuffer)
			free(game->zbuffer);
		if (game->mlx_ptr)
		{
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
		}
		free(game);
	}
	else if (exit_code == 1 || exit_code == 2)
		draw_finish_hud(game, exit_code);
}
