/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:34:57 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:58:09 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_strtrim
** -----------------
** Elimina los caracteres especificados en 'set' del principio y el final
** de la cadena 's1'.
**
** PARAMETROS:
** - char const *s1: La cadena de entrada.
** - char const *set: La cadena de caracteres a eliminar.
**
** RETORNO:
** - Un puntero a la nueva cadena resultante.
** - NULL si la reserva de memoria falla o si s1 o set son NULL.
**
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}
