/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:16:16 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:58:33 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_substr
** -----------------
** Crea una subcadena de la cadena s, comenzando en el índice start y
** con una longitud de len caracteres.
**
** PARAMETROS:
** - char const *s: La cadena de entrada.
** - unsigned int start: El índice de inicio de la subcadena.
** - size_t len: La longitud de la subcadena.
**
** RETORNO:
** - Un puntero a la nueva subcadena.
** - NULL si la reserva de memoria falla o si s es NULL.
**
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
