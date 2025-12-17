/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:11:27 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:49:50 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_memcpy
** -----------------
** Copia n bytes de la memoria apuntada por src a la memoria apuntada por
** dest. No se garantiza la seguridad de la memoria, por lo que se debe
** asegurar que las áreas de memoria no se superponen.
**
** PARAMETROS:
** - void *dest: Puntero a la memoria de destino.
** - const void *src: Puntero a la memoria de origen.
** - size_t n: Número de bytes a copiar.
**
** RETORNO:
** - Un puntero a la memoria de destino (dest).
**
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
