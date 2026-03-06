/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse_bonus.h"

/**
 * ENGLISH: Converts individual RGB components to a single packed
 *          hexadecimal colour value (0xRRGGBB).
 *
 * SPANISH: Convierte componentes RGB individuales a un valor de color
 *          hexadecimal empaquetado (0xRRGGBB).
 *
 * @param r Red component (0-255). / Componente rojo (0-255).
 * @param g Green component (0-255). / Componente verde (0-255).
 * @param b Blue component (0-255). / Componente azul (0-255).
 *
 * @return Colour in hexadecimal format. / Color en formato hexadecimal.
 */
int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/**
 * ENGLISH: Validates the RGB string format: exactly 2 commas, only
 *          digits and commas, no embedded spaces (trailing allowed).
 *
 * SPANISH: Valida el formato de la cadena RGB: exactamente 2 comas, solo
 *          dígitos y comas, sin espacios intercalados (al final sí).
 *
 * @param values The raw RGB string to validate. /
 *               La cadena RGB sin procesar a validar.
 *
 * @return 0 if valid, -1 if the format is incorrect. /
 *         0 si es válido, -1 si el formato es incorrecto.
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
