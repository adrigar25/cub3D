/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:23:15 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:57:23 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_strnstr
** -----------------
** Busca la primera aparición de la cadena little en la cadena big,
** limitando la búsqueda a len caracteres.
**
** PARAMETROS:
** - const char *big: La cadena en la que se busca.
** - const char *little: La cadena que se busca.
** - size_t len: El número máximo de caracteres a buscar.
**
** RETORNO:
** - Un puntero a la primera aparición de little en big.
** - NULL si little no se encuentra o si len es 0.
**
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (i + j < len && big[i + j] == little[j])
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
