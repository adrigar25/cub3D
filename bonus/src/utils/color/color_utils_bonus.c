/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/19 17:45:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse_bonus.h"

/**
 * @brief Converts RGB color values to hexadecimal format
 *
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @return int Color in hexadecimal format (0xRRGGBB)
 */
int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

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
