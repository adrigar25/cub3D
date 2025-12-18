/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:05:47 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/18 15:05:53 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_rgb(char *line, int *color)
{
	char	*first_comma;
	char	*second_comma;

	first_comma = ft_strchr(line, ',');
	second_comma = ft_strchr(first_comma + 1, ',');
	color[0] = ft_atoi(line + 2);
	color[1] = ft_atoi(first_comma + 1);
	color[2] = ft_atoi(second_comma + 1);
}
