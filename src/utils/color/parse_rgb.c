/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:05:47 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/23 15:28:18 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_rgb(char *line)
{
	int		red;
	int		green;
	int		blue;
	char	*first_comma;
	char	*second_comma;

	printf("Parsing RGB from line: '%s'\n", line);
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
