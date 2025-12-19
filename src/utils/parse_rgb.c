/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:05:47 by adriescr          #+#    #+#             */
/*   Updated: 2025/12/19 12:38:48 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_rgb(char *line, int *color)
{
	char *first_comma;
	char *second_comma;

	first_comma = ft_strchr(line, ',');
	second_comma = ft_strchr(first_comma + 1, ',');
	color = rbg
