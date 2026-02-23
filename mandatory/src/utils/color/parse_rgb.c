/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:05:47 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/22 19:41:10 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

/**
 * ENGLISH: Parses a string containing RGB color values and converts it to a
 * 			 hexadecimal color code. The input string should be in the format
 * 			 "R,G,B" where R, G, and B are integers between 0 and 255.
 * 			 The function checks the format of the input string and validates
 * 			 the RGB values before converting them to hexadecimal.
 *
 * SPANISH: Analiza una cadena que contiene valores de color RGB y los convierte
 * 			a un código de color hexadecimal. La cadena de entrada debe estar
 * 			en el formato "R,G,B" donde R, G y B son enteros entre 0 y 255.
 * 			La función verifica el formato de la cadena de entrada y valida los
 * 			valores RGB antes de convertirlos a hexadecimal.
 *
 * @param line A string containing the RGB values to be parsed. / Una cadena que
 * 			 contiene los valores RGB a analizar.
 *
 * @return The hexadecimal color code if the input is valid, -2 if the format is
 * 			incorrect or if any RGB value is out of range. / El código de color
 * 			hexadecimal si la entrada es válida, -2 si el formato es incorrecto
 * 			o si algún valor RGB está fuera de rango.
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
