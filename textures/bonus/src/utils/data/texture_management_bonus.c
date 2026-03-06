/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_management_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:00:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "parse_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Appends a new texture node to the end of the sprite linked
 *          list stored in the game structure.
 *
 * SPANISH: Añade un nuevo nodo de textura al final de la lista enlazada
 *          de sprites almacenada en la estructura del juego.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param new_texture Pointer to the texture to append. /
 *                    Puntero a la textura a añadir.
 *
 * @return Always 0. / Siempre 0.
 */
int	push_texture(t_game *game, t_texture *new_texture)
{
	t_texture	*current;

	if (!game->sprites)
	{
		game->sprites = new_texture;
		return (0);
	}
	current = game->sprites;
	while (current->next)
		current = current->next;
	current->next = new_texture;
	return (0);
}

/**
 * ENGLISH: Assigns the texture pointer to the correct game field based
 *          on the key string (NO/SO/WE/EA/DO/X1/X2/X3/A).
 *
 * SPANISH: Asigna el puntero de textura al campo correcto del juego
 *          según la clave (NO/SO/WE/EA/DO/X1/X2/X3/A).
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param key The texture identifier string. / La cadena identificadora.
 * @param texture Pointer to the texture to assign. /
 *                Puntero a la textura a asignar.
 *
 * @return 1 if a wall/entity field was assigned, 0 otherwise. /
 *         1 si se asignó un campo de pared/entidad, 0 en caso contrario.
 */
int	assign_wall_texture(t_game *game, char *key, t_texture *texture)
{
	if (!ft_strcmp(key, "DO") || !ft_strcmp(key, "X1") || !ft_strcmp(key, "X2")
		|| !ft_strcmp(key, "X3") || !ft_strcmp(key, "A"))
		update_allowed_chars(game, key[0]);
	if (!ft_strcmp(key, "SO"))
		game->txt_so = texture;
	else if (!ft_strcmp(key, "NO"))
		game->txt_no = texture;
	else if (!ft_strcmp(key, "WE"))
		game->txt_we = texture;
	else if (!ft_strcmp(key, "EA"))
		game->txt_ea = texture;
	else if (!ft_strcmp(key, "DO"))
		game->txt_door = texture;
	else if (!ft_strcmp(key, "X1"))
		game->e_txt_s = texture;
	else if (!ft_strcmp(key, "X2"))
		game->e_txt_w1 = texture;
	else if (!ft_strcmp(key, "X3"))
		game->e_txt_w2 = texture;
	else if (!ft_strcmp(key, "A"))
		game->txt_exit = texture;
	else
		return (0);
	return (1);
}

/**
 * ENGLISH: Allocates a new t_texture node and copies the key and path
 *          strings into it.
 *
 * SPANISH: Reserva un nuevo nodo t_texture y copia en él las cadenas
 *          de clave y ruta.
 *
 * @param key The texture identifier. / El identificador de textura.
 * @param value The file path string. / La cadena de ruta de archivo.
 *
 * @return Pointer to the new texture, or NULL on allocation failure. /
 *         Puntero a la nueva textura, o NULL si falla la reserva.
 */
t_texture	*create_texture(char *key, char *value)
{
	t_texture	*new_texture;

	new_texture = malloc(sizeof(t_texture));
	if (!new_texture)
		return (NULL);
	new_texture->name = ft_strtrim(key, " \t\n");
	new_texture->path = ft_strdup(value);
	new_texture->next = NULL;
	return (new_texture);
}

/**
 * ENGLISH: Returns 1 if the given key is already registered as a wall,
 *          entity, or sprite texture in the game structure.
 *
 * SPANISH: Retorna 1 si la clave dada ya está registrada como textura
 *          de pared, entidad o sprite en la estructura del juego.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param key Texture key string to check. /
 *            Cadena de clave de textura a comprobar.
 *
 * @return 1 if duplicate, 0 if new. / 1 si es duplicado, 0 si es nuevo.
 */
static int	is_text_duplicate(t_game *game, char *key)
{
	t_texture	*cur;

	if ((!ft_strcmp(key, "NO") && game->txt_no) || (!ft_strcmp(key, "SO")
			&& game->txt_so) || (!ft_strcmp(key, "WE") && game->txt_we)
		|| (!ft_strcmp(key, "EA") && game->txt_ea) || (!ft_strcmp(key, "DO")
			&& game->txt_door) || (!ft_strcmp(key, "X1") && game->e_txt_s)
		|| (!ft_strcmp(key, "X2") && game->e_txt_w1) || (!ft_strcmp(key, "X3")
			&& game->e_txt_w2) || (!ft_strcmp(key, "A") && game->txt_exit))
		return (1);
	cur = game->sprites;
	while (cur)
	{
		if (cur->name && !ft_strcmp(cur->name, key))
			return (1);
		cur = cur->next;
	}
	return (0);
}

/**
 * ENGLISH: Creates a new texture from the key/value pair, checks for
 *          duplicates, assigns it to a wall field or pushes it to the
 *          sprites list, and updates allowed characters if needed.
 *
 * SPANISH: Crea una nueva textura a partir del par clave/valor, comprueba
 *          duplicados, la asigna a un campo de pared o la añade a la lista
 *          de sprites, y actualiza los caracteres permitidos si es necesario.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param key Texture identifier. / Identificador de textura.
 * @param value File path. / Ruta de archivo.
 *
 * @return 0 on success, -1 on error. / 0 en éxito, -1 en error.
 */
int	process_texture(t_game *game, char *key, char *value)
{
	t_texture	*new_texture;
	char		*trimmed_key;

	trimmed_key = ft_strtrim(key, " \t\n");
	if (!trimmed_key)
		return (-1);
	if (is_text_duplicate(game, trimmed_key))
	{
		ft_fprintf(2, RED "Error: Duplicate texture key '%s'\n" RESET,
			trimmed_key);
		free(trimmed_key);
		return (-1);
	}
	free(trimmed_key);
	new_texture = create_texture(key, value);
	if (!new_texture)
		return (-1);
	if (assign_wall_texture(game, key, new_texture))
		return (0);
	push_texture(game, new_texture);
	if (new_texture->name && new_texture->name[0])
		update_allowed_chars(game, new_texture->name[0]);
	return (0);
}
