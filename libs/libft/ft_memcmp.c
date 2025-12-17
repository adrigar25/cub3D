/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:51 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:49:26 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_memcmp
** -----------------
** Compara los primeros n bytes de las cadenas s1 y s2.
**
** PARAMETROS:
** - const void *s1: Puntero a la primera cadena.
** - const void *s2: Puntero a la segunda cadena.
** - size_t n: Número de bytes a comparar.
**
** RETORNO:
** - Un valor menor que 0 si s1 es menor que s2,
** - Un valor mayor que 0 si s1 es mayor que s2,
** - 0 si son iguales.
**
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s3 = (const unsigned char *)s1;
	const unsigned char	*s4 = (const unsigned char *)s2;

	while (n--)
	{
		if (*s3 != *s4)
			return (*s3 - *s4);
		s3++;
		s4++;
	}
	return (0);
}
