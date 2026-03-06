/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:45:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/23 15:57:27 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ENGLISH: Trims all occurrences of characters in set from the start
 *          and end of the given string.
 *
 * SPANISH: Elimina todas las ocurrencias de los caracteres en set
 *          del inicio y el final de la cadena dada.
 *
 * @param s1   The string to be trimmed. /
 *             La cadena a ser recortada.
 *
 * @param set  The set of characters to trim from the string. /
 *             El conjunto de caracteres a eliminar de la cadena.
 *
 * @returns A pointer to the newly allocated trimmed string. /
 *          Un puntero a la nueva cadena recortada asignada.
 * @returns Returns NULL if memory allocation fails or if s1 is NULL. /
 *          Devuelve NULL si la asignación de memoria falla o si s1 es NULL.
 */

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_isinset(s1[start], set))
		start++;
	while (end >= start && ft_isinset(s1[end], set))
		end--;
	len = end - start + 1;
	if (len <= 0)
		return (ft_strdup(""));
	trimmed = malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, len + 1);
	return (trimmed);
}
