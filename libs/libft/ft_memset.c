/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:28:38 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:51:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_memset
** -----------------
** Establece los primeros n bytes de la memoria apuntada por s al valor c.
**
** PARAMETROS:
** - void *s: Puntero a la memoria que se va a establecer.
** - int c: Valor a establecer en la memoria.
** - size_t n: Número de bytes a establecer.
**
** RETORNO:
** - Devuelve un puntero a la memoria original apuntada por s.
**
*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}
