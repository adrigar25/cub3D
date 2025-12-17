/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:26:18 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:56:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_strlcpy
** -----------------
** Copia hasta size - 1 caracteres de la cadena src a dest, asegurando que
** dest siempre esté terminada en nulo. Si src es más larga que size,
** se trunca.
**
** PARAMETROS:
** - char *dest: La cadena de destino donde se copiará src.
** - const char *src: La cadena de origen que se copiará a dest.
** - unsigned int size: El tamaño máximo de la cadena dest.
**
** RETORNO:
** - La longitud total de la cadena que se habría creado si no hubiera
**   limitaciones de tamaño. Esto es la longitud de src.
** - Si size es 0, se devuelve la longitud de src.
**
*/

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	src_len;
	unsigned int	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (src_len);
}
