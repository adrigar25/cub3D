/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:02:26 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:36:32 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCIÓN: ft_bzero
** -----------------
** Establece los primeros n bytes de la memoria apuntada por s a cero.
**
** PARÁMETROS:
** - void *s: Puntero a la memoria que se va a establecer en cero.
** - size_t n: Número de bytes a establecer en cero.
**
** RETORNO:
** - Devuelve un puntero a la memoria original apuntada por s.
**
*/

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = '\0';
		ptr++;
	}
	return (s);
}
