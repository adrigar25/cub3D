/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:11:15 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:50:21 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_memmove
** -----------------
** Copia n bytes de la memoria apuntada por src a la memoria apuntada por
** dest. Si las áreas de memoria se superponen, la copia se realiza de
** manera segura.
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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s && d < s + n)
		while (n--)
			d[n] = s[n];
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}
