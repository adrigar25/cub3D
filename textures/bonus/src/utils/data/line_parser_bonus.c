/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:00:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/22 19:21:29 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "parse_bonus.h"

/**
 * ENGLISH: Update the list of allowed characters for map validation.
 *
 *
 * SPANISH: Actualiza la lista de caracteres permitidos
 *			para validación del mapa.
 */
void	update_allowed_chars(t_game *game, char c)
{
	int	i;
	int	exists;

	exists = 0;
	i = 0;
	while (i < game->allowed_count)
	{
		if (game->allowed_chars[i] == c)
			exists = 1;
		i++;
	}
	if (!exists)
	{
		game->allowed_chars[game->allowed_count++] = c;
		game->allowed_chars[game->allowed_count] = '\0';
	}
}

int	process_color(t_game *game, char *key, char *value)
{
	int	*color;

	color = NULL;
	if (!ft_strcmp(key, "C"))
		color = &game->ceiling_color;
	else if (!ft_strcmp(key, "F"))
		color = &game->floor_color;
	if (*color != -1)
	{
		ft_fprintf(2, RED "Error: Duplicated color:%s\n" RESET, key);
		return (-1);
	}
	*color = parse_rgb(value);
	return (*color);
}

/**
 * ENGLISH: Parse a configuration line from the file (texture, color, etc).
 *
 * SPANISH: Parsea una línea de configuración del archivo (textura, color, etc).
 */
int	process_config_line(t_game *game, char *line)
{
	char	*temp;
	char	*raw_key;
	char	*key;
	char	*value;
	int		result;

	result = 0;
	temp = ft_strtrim(line, " \t\n");
	if (!temp || temp[0] == '\0')
		return (free(temp), 0);
	raw_key = ft_substr(temp, 0, 2);
	if (!raw_key)
		return (free(temp), 0);
	key = ft_strtrim(raw_key, " \t\n");
	value = ft_strtrim(temp + 2, " \t\n");
	if (!key || !value)
		return (free(temp), free(raw_key), free(key), free(value), 0);
	if (!ft_strcmp(key, "C") || !ft_strcmp(key, "F"))
		result = process_color(game, key, value);
	else
		result = process_texture(game, key, value);
	return (free(temp), free(raw_key), free(key), free(value), result);
}
