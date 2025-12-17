/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:05:37 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:48:51 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_memchr
** -----------------
** Busca la primera aparición del carácter c en los primeros n bytes
** de la cadena s.
**
** PARAMETROS:
** - const void *s: Puntero a la cadena donde se realiza la búsqueda.
** - int c: Carácter a buscar.
** - size_t n: Número de bytes a buscar.
**
** RETORNO:
** - Puntero a la primera aparición de c en s, o NULL si no se encuentra.
**
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
