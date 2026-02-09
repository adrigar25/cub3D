/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:00:00 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/09 16:56:25 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

/**
 * ENGLISH: Update the list of allowed characters for map validation.
 *
 * SPANISH: Actualiza la lista de caracteres permitidos para validación del mapa.
 */
void	update_allowed_chars(t_game *game, char c)
{
	int	i;
	int	exists;

	exists = 0;
	i = -1;
	while (i++ < game->allowed_count)
		if (game->allowed_chars[i] == c)
			exists = 1;
	if (!exists)
	{
		game->allowed_chars[game->allowed_count++] = c;
		game->allowed_chars[game->allowed_count] = '\0';
	}
}

/**
 * ENGLISH: Parse a configuration line from the file (texture, color, etc).
 *
 * SPANISH: Parsea una línea de configuración del archivo (textura, color, etc).
 */
int	process_config_line(t_game *game, char *line)
{
	char	*temp;
	char	*key;
	char	*key2;
	char	*value;
	int		result;

	result = 0;
	temp = ft_strtrim(line, " \t\n");
	if (!temp || temp[0] == '\0')
		return (free(temp), 0);
	key = ft_substr(temp, 0, 2);
	key2 = ft_strtrim(key, " \t\n");
	value = ft_strtrim(temp + 2, " \t\n");
	if (!ft_strcmp(key2, "C"))
		game->ceiling_color = parse_rgb(value);
	else if (!ft_strcmp(key2, "F"))
		game->floor_color = parse_rgb(value);
	else
		result = process_texture(game, key2, value);
	printf("DBG processed line: key='%s' value='%s'\n", key2, value);
	free(temp);
	free(key);
	free(key2);
	free(value);
	return (result);
}
