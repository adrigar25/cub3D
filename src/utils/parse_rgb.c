/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:05:47 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/19 12:40:41 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_rgb(char *line)
{
	int		color;
	char	*first_comma;
	char	*second_comma;

	first_comma = ft_strchr(line, ',');
	second_comma = ft_strchr(first_comma + 1, ',');
	color = rgb_to_hex(ft_atoi(line + 2), ft_atoi(first_comma + 1),
			ft_atoi(second_comma + 1));
	return (color);
}
