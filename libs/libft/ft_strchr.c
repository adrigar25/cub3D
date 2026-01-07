/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:17:18 by adriescr          #+#    #+#             */
/*   Updated: 2026/01/07 14:19:27 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ENGLISH: Locates the first occurrence of a character in a string.
 *
 * SPANISH: Localiza la primera ocurrencia de un carácter en una cadena.
 *
 * @param str   The string to search. /
 *            La cadena a buscar.
 * @param c   The character to find. /
 *            El carácter a encontrar.
 *
 * @returns A pointer to the first occurrence of the character, or NULL
 * 			if not found. / Un puntero a la primera ocurrencia del carácter,
 * 			o NULL si no se encuentra.
 */
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
