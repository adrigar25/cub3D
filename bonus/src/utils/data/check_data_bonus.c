/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:08:58 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"
#include "parse_bonus.h"
#include <unistd.h>

/**
 * ENGLISH: Iterates the sprite linked list and verifies that every
 *          texture has a valid, accessible file path.
 *
 * SPANISH: Itera la lista enlazada de sprites y verifica que cada
 *          textura tiene una ruta de archivo válida y accesible.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 1 if all sprite textures exist, 0 on first missing one. /
 *         1 si todas las texturas existen, 0 con la primera ausente.
 */
static int	check_sprites(t_game *game)
{
	t_texture	*current;

	current = game->sprites;
	while (current)
	{
		if (!current->path || access(current->path, F_OK) == -1)
		{
			ft_fprintf(2, RED "Error: Sprite texture file");
			if (current->path)
				ft_fprintf(2, " '%s'", current->path);
			ft_fprintf(2, " not found\n" RESET);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

/**
 * ENGLISH: Checks that a texture pointer is non-NULL and its file path
 *          exists on disk; prints a labelled error message if not.
 *
 * SPANISH: Comprueba que el puntero de textura no es NULL y que su ruta
 *          existe en disco; imprime mensaje de error etiquetado si no.
 *
 * @param texture Pointer to the texture to validate. /
 *                Puntero a la textura a validar.
 * @param label Human-readable name for error output. /
 *              Nombre legible para la salida de error.
 *
 * @return 1 if valid or NULL (optional), 0 on missing path. /
 *         1 si es válida o NULL (opcional), 0 si falta la ruta.
 */
static int	check_texture_file(t_texture *texture, char *label)
{
	if (!texture)
		return ((1));
	if (!texture->path || access(texture->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: %s texture file not found\n" RESET, label);
		return (0);
	}
	return (1);
}

/**
 * ENGLISH: Validates that both floor and ceiling colours have been parsed
 *          and are within valid range (not -1 or -2).
 *
 * SPANISH: Valida que los colores de suelo y techo han sido parseados
 *          y son válidos (ni -1 ni -2).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 1 if both colours are valid, 0 otherwise. /
 *         1 si ambos colores son válidos, 0 en caso contrario.
 */
static int	check_colors(t_game *game)
{
	if (game->floor_color == -1 || game->ceiling_color == -1)
	{
		ft_fprintf(2, RED "Error: Missing floor or ceiling color\n" RESET);
		return (0);
	}
	if (game->ceiling_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid ceiling RGB\n" RESET), 0);
	if (game->floor_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid floor RGB\n" RESET), 0);
	return (1);
}

/**
 * ENGLISH: If enemies exist, verifies that the standing and both walking
 *          animation texture files are accessible on disk.
 *
 * SPANISH: Si hay enemigos, verifica que los archivos de textura de la
 *          animación estática y de las dos caminatas son accesibles.
 *
 * @param enemies Pointer to the enemy list (NULL = no enemies). /
 *                Puntero a la lista de enemigos (NULL = sin enemigos).
 * @param e_txt_s Standing texture. / Textura estática.
 * @param e_txt_w1 Walking frame 1 texture. / Textura animación paso 1.
 * @param e_txt_w2 Walking frame 2 texture. / Textura animación paso 2.
 *
 * @return 1 if all enemy textures are valid or no enemies, else 0. /
 *         1 si las texturas son válidas o no hay enemigos, si no 0.
 */
static int	check_enemy_text(t_enemy *enemies, t_texture *e_txt_s,
		t_texture *e_txt_w1, t_texture *e_txt_w2)
{
	if (enemies == NULL)
		return (1);
	if (!e_txt_s || access(e_txt_s->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: Standing enemy texture not found\n" RESET);
		return (0);
	}
	if (!e_txt_w1 || access(e_txt_w1->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: Walking 1 enemy texture not found\n" RESET);
		return (0);
	}
	if (!e_txt_w2 || access(e_txt_w2->path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: Walking 2 enemy texture not found\n" RESET);
		return (0);
	}
	return (1);
}

/**
 * ENGLISH: Runs all validation checks on parsed game data: wall and
 *          sprite textures, enemy textures, door/exit textures, and
 *          floor/ceiling colours.
 *
 * SPANISH: Ejecuta todas las comprobaciones de validación sobre los
 *          datos del juego: texturas de pared y sprites, texturas de
 *          enemigos, puerta/salida, y colores de suelo y techo.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 0 on success, -1 if any required data is missing or invalid. /
 *         0 en éxito, -1 si falta o es inválido algún dato requerido.
 */
int	check_data(t_game *game)
{
	if (!game->txt_no || !game->txt_so || !game->txt_we || !game->txt_ea)
		return (ft_fprintf(2, RED "Error: Missing textures\n" RESET), -1);
	if (!check_texture_file(game->txt_no, "North"))
		return (-1);
	if (!check_texture_file(game->txt_so, "South"))
		return (-1);
	if (!check_texture_file(game->txt_we, "West"))
		return (-1);
	if (!check_texture_file(game->txt_ea, "East"))
		return (-1);
	if (!check_enemy_text(game->enemies, game->e_txt_s, game->e_txt_w1,
			game->e_txt_w2))
		return (-1);
	if (!check_texture_file(game->txt_door, "Door"))
		return (-1);
	if (!game->txt_exit && has_exit(game->map.grid))
		return (ft_fprintf(2, RED "Error: Missing exit texture\n" RESET), -1);
	if (game->txt_exit && !check_texture_file(game->txt_exit, "Exit"))
		return (-1);
	if (!check_sprites(game))
		return (-1);
	if (!check_colors(game))
		return (-1);
	return (0);
}
