/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/22 19:41:16 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

/**
 * ENGLISH: Converts RGB color values to a hexadecimal color code.
 *
 * SPANISH: Convierte los valores de color RGB a un código de color hexadecimal.
 *
 * @param r The red component of the color (0-255). / El componente rojo del
 * 			color (0-255).
 * @param g The green component of the color (0-255). / El componente verde del
 * 			color (0-255).
 * @param b The blue component of the color (0-255). / El componente azul del
 * 			color (0-255).
 * @return The hexadecimal color code, or -1 if any of the RGB values are out
 * 			of range. / El código de color hexadecimal, o -1 si alguno de los
 * 			valores RGB está fuera de rango.
 */
int	rgb_to_hex(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/**
 * ENGLISH: Checks if the RGB color values are in the correct format, which
 * 			 should be three integers separated by commas, with optional
 * 			 whitespace.
 *
 * SPANISH: Verifica si los valores de color RGB están en el formato correcto,
 * 			 que debe ser tres enteros separados por comas, con espacios
 * 			 opcionales.
 *
 * @param values A string containing the RGB values to be checked. / Una cadena
 * 				que contiene los valores RGB a verificar.
 *
 * @return 0 if the format is correct, or -1 if it is incorrect. / 0 si el
 * 			formato es correcto, o -1 si es incorrecto.
 */
int	check_rgb_format(char *values)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (values[i] && values[i] != '\n')
	{
		if (values[i] == ' ' || values[i] == '\t')
		{
			i++;
			while (values[i] && (values[i] == ' ' || values[i] == '\t'))
				i++;
			if (values[i] && values[i] != '\n')
				return (-1);
			break ;
		}
		if (values[i] == ',')
			comma_count++;
		else if (!ft_is_digit(values[i]))
			return (-1);
		i++;
	}
	if (comma_count != 2)
		return (-1);
	return (0);
}
