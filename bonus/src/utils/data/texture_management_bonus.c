/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_management_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:00:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "libft.h"
#include "parse_bonus.h"
#include <stdlib.h>

/**
 * ENGLISH: Add a texture to the sprite linked list.
 *
 * SPANISH: Añade una textura a la lista enlazada de sprites.
 */
int	push_texture(t_game *game, t_texture *new_texture) {
  t_texture *current;

  if (!game->sprites) {
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
 * ENGLISH: Assign texture to corresponding wall direction or entity.
 *
 * SPANISH: Asigna la textura a la dirección de pared o entidad correspondiente.
 */
int	assign_wall_texture(t_game *game, char *key, t_texture *texture) {
  if (!ft_strcmp(key, "DO") || !ft_strcmp(key, "X1") || !ft_strcmp(key, "X2") ||
      !ft_strcmp(key, "X3"))
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
 * ENGLISH: Create a new texture structure with key and path.
 *
 * SPANISH: Crea una nueva estructura de textura con clave y ruta.
 */
t_texture	*create_texture(char *key, char *value) {
  t_texture *new_texture;

  new_texture = malloc(sizeof(t_texture));
  if (!new_texture)
    return (NULL);
  new_texture->name = ft_strtrim(key, " \t\n");
  new_texture->path = ft_strdup(value);
  new_texture->next = NULL;
  return (new_texture);
}

/**
 * ENGLISH: Process texture data: create, assign or add to sprite list.
 *
 * SPANISH: Procesa datos de textura: crear,
        asignar o añadir a lista de sprites.
 */
int	process_texture(t_game *game, char *key, char *value) {
  t_texture *new_texture;

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
