/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:05:47 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse_bonus.h"

/**
 * ENGLISH: Parses a comma-separated "R,G,B" string, validates the format
 *          and range, and returns the packed hex colour.
 *
 * SPANISH: Parsea una cadena "R,G,B" separada por comas, valida el
 *          formato y el rango, y retorna el color hexadecimal empaquetado.
 *
 * @param line The RGB string to parse. / La cadena RGB a parsear.
 *
 * @return Packed hex colour on success, or -2 on invalid input. /
 *         Color hex empaquetado en éxito, o -2 en entrada inválida.
 */
int	parse_rgb(char *line)
{
	int		red;
	int		green;
	int		blue;
	char	*first_comma;
	char	*second_comma;

	if (check_rgb_format(line) == -1)
		return (-2);
	first_comma = ft_strchr(line, ',');
	second_comma = ft_strchr(first_comma + 1, ',');
	if (!first_comma || !second_comma)
		return (-2);
	red = ft_atoi(line);
	green = ft_atoi(first_comma + 1);
	blue = ft_atoi(second_comma + 1);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
		return (-2);
	return (rgb_to_hex(red, green, blue));
}
