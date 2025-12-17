/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:37:59 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:55:48 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_strlcat
** -----------------
** Concatena la cadena src al final de la cadena dest, asegurando que
** dest tiene un tamaño máximo de size bytes. La cadena resultante
** siempre estará terminada en nulo.
**
** PARAMETROS:
** - char *dest: La cadena de destino a la que se concatenará src.
** - const char *src: La cadena de origen que se concatenará a dest.
** - unsigned int size: El tamaño máximo de la cadena dest.
**
** RETORNO:
** - El tamaño total de la cadena que se habría creado si no hubiera
**   limitaciones de tamaño. Esto es la longitud de dest más la
**   longitud de src.
** - Si size es menor o igual a la longitud de dest, se devuelve
**   src_len + size.
**
*/

int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;
	unsigned int	j;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (src_len + size);
	i = dest_len;
	j = 0;
	while (src[j] != '\0' && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
